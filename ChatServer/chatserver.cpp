#include "chatserver.h"
#include "serverworker.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>


ChatServer::ChatServer(QObject *parent)
    :QTcpServer(parent) {

    m_pool = new QThreadPool(this);
    m_pool->setMaxThreadCount(10); // 设置最大线程数

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="D:/课程/QT/实验/大作业/qtExperiment.db";
    db.setDatabaseName(aFile);//设置数据库名称
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
    }
    // if (!this->listen(QHostAddress::Any, 1967)) {
    //     qDebug() << "Server could not start!";
    // } else {
    //     qDebug() << "Server started on port 1967";
    // }
}

ChatServer::~ChatServer()
{
    m_pool->waitForDone();
    delete m_pool;
}

void ChatServer::run(){}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker=new ServerWorker(this);

    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();//该函数执行后再删除
        return;
    }
    connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker, &ServerWorker::jsonReceived, this, &ChatServer::jsonReceived, Qt::QueuedConnection);
    connect(worker, &ServerWorker::disconnectFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));

    // 创建一个新的线程并移动 worker 到该线程
    QThread *thread = new QThread;
    worker->moveToThread(thread);
    thread->start();
    m_clients.append(worker);//连接成功，就将该客户端放进m_clients列表中
    emit logMessage("新的用户连接上了");//有新连接就发一个消息

}


void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    m_clientListMutex.lock();
    for (ServerWorker *worker : m_clients) {
        if (worker!= exclude) {
            qDebug() << "Broadcasting message to" << worker->userName();
            worker->sendJson(message);
        }
    }
    m_clientListMutex.unlock();
}


void ChatServer::stopServer()
{
    close();//调用QTcpServer的close()
    m_pool->clear();
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if(typeVal.isNull() || !typeVal.isString())
        return;

    if(typeVal.toString().compare("message",Qt::CaseInsensitive) == 0){

        const QJsonValue textVal =docObj.value("text");
        if(textVal.isNull() || !textVal.isString())
            return;
        const QString text = textVal.toString().trimmed();//获取类型为type的文本内容
        if(text.isEmpty())
            return;

        QJsonObject message;
        message["type"] = "message";
        message["text"] = text;
        message["sender"] = sender->userName();//服务器转发消息时要声明是转发给哪个客户端
        bool isAdmin = docObj.contains("is_admin") && docObj.value("is_admin").toBool();
        // 如果发送者是管理员，修改消息格式
        if (isAdmin) {
            qDebug() << "Server sender admin status: " << sender->isAdmin();
            message["sender"] = sender->userName() + "[管理员]";
        }
        else {
            message["sender"] = sender->userName();
        }

        // 保存聊天记录到数据库
        QSqlQuery query(db);
        query.prepare("INSERT INTO chat_history (sender, message, is_admin) VALUES (:sender, :message, :is_admin)");
        query.bindValue(":sender", sender->userName());
        query.bindValue(":message", text);
        query.bindValue(":is_admin", isAdmin);
        if (!query.exec()) {
            qDebug() << "Failed to insert into chat_history:" << query.lastError();
        }

        broadcast(message, sender);
    }
    else if(typeVal.toString().compare("login",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("text");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        sender->setUserName(usernameVal.toString());
        // 获取登录消息中的管理员权限信息并设置
        const QJsonValue isAdminVal = docObj.value("is_admin");
        if (isAdminVal.isBool()) {
            sender->setIsAdmin(isAdminVal.toBool());
            qDebug() << "User " << usernameVal.toString() << " is admin.";
        }else {
            // 如果没有 is_admin 字段，默认设置为非管理员
            sender->setIsAdmin(false);
            qDebug() << "User " << usernameVal.toString() << " is not admin.";
        }

        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["username"] = usernameVal.toString();
        connectedMessage["is_muted"] = m_isMuted; // 添加当前禁言状态
        broadcast(connectedMessage, sender);

        QJsonObject userListMessage;
        userListMessage["type"] = "userList";
        QJsonArray userlist;
        for(ServerWorker *worker : m_clients){

            if(worker == sender)
                userlist.append("📝" + worker->userName());//若在本窗口发送消息，则在该用户名前加*
            else
                userlist.append(worker->userName());
        }
        userListMessage["userlist"] = userlist;
        sender->sendJson(userListMessage);
    }
    else if (typeVal.toString().compare("private", Qt::CaseInsensitive) == 0) {
            const QJsonValue targetVal = docObj.value("target");
            if (targetVal.isNull() ||!targetVal.isString())
                return;

            const QString target = targetVal.toString();
            const QJsonValue textVal = docObj.value("text");

            if (textVal.isNull() ||!textVal.isString())
                return;
            const QString text = textVal.toString().trimmed();
            if (text.isEmpty())
                return;

            QJsonObject privateMessage;
            privateMessage["type"] = "private";
            privateMessage["text"] = text;
            //privateMessage["sender"] = sender->userName();
            // 如果发送者是管理员，修改消息格式
            bool isAdmin = docObj.contains("is_admin") && docObj.value("is_admin").toBool();
            if (isAdmin) {
                privateMessage["sender"] = sender->userName() + "[管理员]";
            }else {
                privateMessage["sender"] = sender->userName();
            }
            for (ServerWorker *worker : m_clients) {
                if (worker->userName() == target) {
                    worker->sendJson(privateMessage);
                    break;
                }
            }
    }
    else if(typeVal.toString().compare("kick", Qt::CaseInsensitive) == 0){
        // 检查发送者是否为管理员
        const QJsonValue isAdminVal = docObj.value("is_admin");
        if (isAdminVal.isBool() && isAdminVal.toBool()) {
            const QJsonValue targetVal = docObj.value("target");
            if (targetVal.isNull() ||!targetVal.isString())
                return;

            const QString targetUsername = targetVal.toString();
            // 广播用户被踢出的消息给其他客户端（排除发送者）
            QJsonObject kickedMessage;
            kickedMessage["type"] = "userKicked";
            kickedMessage["username"] = targetUsername;
            broadcast(kickedMessage, sender);

            // 发送被踢出消息给目标客户端，并断开连接
            QJsonObject kickNotice;
            kickNotice["type"] = "userKicked";
            kickNotice["username"] = targetUsername;
            ServerWorker *targetWorker = nullptr;
            for (ServerWorker *worker : m_clients) {
                if (worker->userName() == targetUsername) {
                    targetWorker = worker;
                    break;
                }
            }
            if (targetWorker) {
                //targetWorker->sendJson(kickNotice); // 通知目标用户
                targetWorker->disconnectFromClient();
                m_clients.removeAll(targetWorker);
            }
        }
        return;
    }
    else if (typeVal.toString().compare("disconnect", Qt::CaseInsensitive) == 0) {
        // 直接调用userDisconnected函数来处理用户断开连接情况
        userDisconnected(sender);
        return;
    }
    else if (typeVal.toString().compare("mute", Qt::CaseInsensitive) == 0){
        bool isAdmin = docObj.contains("is_admin") && docObj.value("is_admin").toBool();
        if(!isAdmin){
            qDebug()<<"不是管理员";
            return;
        }

        QString senderName = docObj.value("sender").toString();
        qDebug() << "Server received mute message from" << senderName;
\
        m_isMuted = true;
        qDebug() << "Server: Mute activated by admin.";
        emit logMessage("管理员开启禁言");

        QJsonObject muteMessage;
        muteMessage["type"]="mute";
        muteMessage["is_muted"] = true;
        broadcast(muteMessage,nullptr);
    }
    else if(typeVal.toString().compare("unmute", Qt::CaseInsensitive) == 0){
        bool isAdmin = docObj.contains("is_admin") && docObj.value("is_admin").toBool();
        if(!isAdmin){
            qDebug()<<"不是管理员";
            return;
        }

        m_isMuted = false; // 更新全局禁言状态
        qDebug() << "Server: Unmute activated by admin.";
        emit logMessage("管理员解除禁言");
        QJsonObject unmuteMessage;
        unmuteMessage["type"]="unmute";
        unmuteMessage["is_muted"] = false;
        broadcast(unmuteMessage, nullptr);
    }
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clientListMutex.lock();
    m_clients.removeAll(sender);//从列表中移除sender
    m_clientListMutex.unlock();

    const QString userName = sender->userName();
    if(!userName.isEmpty()){
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = "userdisconnected";
        disconnectedMessage["username"] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + " disconnected");
    }
    sender->deleteLater();
}
