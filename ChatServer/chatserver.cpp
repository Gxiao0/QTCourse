#include "chatserver.h"
#include "serverworker.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
<<<<<<< HEAD
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
}

ChatServer::~ChatServer()
{
    m_pool->waitForDone();
    delete m_pool;
}

void ChatServer::run(){}
=======

ChatServer::ChatServer(QObject *parent):QTcpServer(parent)
{

}
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker=new ServerWorker(this);
<<<<<<< HEAD

    if(!worker->setSocketDescriptor(socketDescriptor)){
        worker->deleteLater();//该函数执行后再删除
        return;
    }
    connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
    connect(worker, &ServerWorker::jsonReceived, this, &ChatServer::jsonReceived);
    connect(worker, &ServerWorker::disconnectFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));

        // 创建一个新的线程并移动 worker 到该线程
    QThread *thread = new QThread;
    worker->moveToThread(thread);
    thread->start();
    m_clients.append(worker);//连接成功，就将该客户端放进m_clients列表中
    emit logMessage("新的用户连接上了");//有新连接就发一个消息
=======
        if(!worker->setSocketDescriptor(socketDescriptor)){
            worker->deleteLater();//该函数执行后再删除
            return;
        }
        connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
        connect(worker, &ServerWorker::jsonReceived, this, &ChatServer::jsonReceived);
        connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));

        m_clients.append(worker);//连接成功，就将该客户端放进m_clients列表中
        emit logMessage("新的用户连接上了");//有新连接就发一个消息
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

}


<<<<<<< HEAD
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
=======

void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker: m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::stopServer()
{
    close();//调用QTcpServer的close()
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
}

void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &docObj)
{
<<<<<<< HEAD

=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
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
<<<<<<< HEAD
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
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

        broadcast(message, sender);
    }
    else if(typeVal.toString().compare("login",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("text");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        sender->setUserName(usernameVal.toString());
<<<<<<< HEAD
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

=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
        QJsonObject connectedMessage;
        connectedMessage["type"] = "newuser";
        connectedMessage["username"] = usernameVal.toString();
        broadcast(connectedMessage, sender);

        QJsonObject userListMessage;
        userListMessage["type"] = "userList";
        QJsonArray userlist;
        for(ServerWorker *worker : m_clients){
            if(worker == sender)
                userlist.append(worker->userName() + "*");//若在本窗口发送消息，则在该用户名前加*
            else
                userlist.append(worker->userName());
        }
        userListMessage["userlist"] = userlist;
        sender->sendJson(userListMessage);
    }
<<<<<<< HEAD
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
    else if(typeVal.toString().compare("mute", Qt::CaseInsensitive) == 0){
        // 管理员发来的禁言消息
        if (sender->isAdmin()) { // 需要检查发起禁言请求的用户是否为管理员
            m_isMuted = true; // 更新全局禁言状态
            qDebug() << "Server: Mute activated by admin.";
            emit logMessage("管理员开启禁言");
            broadcast(QJsonObject{{"type", "mute"}}, sender);
       }
    }
    else if(typeVal.toString().compare("unmute", Qt::CaseInsensitive) == 0){
        if (sender->isAdmin()) { // 需要检查发起解除禁言请求的用户是否为管理员
            m_isMuted = false; // 更新全局禁言状态
            qDebug() << "Server: Unmute activated by admin.";
            emit logMessage("管理员解除禁言");
            broadcast(QJsonObject{{"type", "unmute"}}, sender);
        }
    }
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
<<<<<<< HEAD
    m_clientListMutex.lock();
    m_clients.removeAll(sender);//从列表中移除sender
    m_clientListMutex.unlock();

=======
    m_clients.removeAll(sender);//只从列表中移除sender
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
    const QString userName = sender->userName();
    if(!userName.isEmpty()){
        QJsonObject disconnectedMessage;
        disconnectedMessage["type"] = "userdisconnected";
        disconnectedMessage["username"] = userName;
        broadcast(disconnectedMessage, nullptr);
        emit logMessage(userName + "disconnected");
    }
    sender->deleteLater();
}
<<<<<<< HEAD




=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
