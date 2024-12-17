#include "chatserver.h"
#include "serverworker.h"
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

ChatServer::ChatServer(QObject *parent):QTcpServer(parent)
{

}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWorker *worker=new ServerWorker(this);
        if(!worker->setSocketDescriptor(socketDescriptor)){
            worker->deleteLater();//该函数执行后再删除
            return;
        }
        connect(worker,&ServerWorker::logMessage,this,&ChatServer::logMessage);
        connect(worker, &ServerWorker::jsonReceived, this, &ChatServer::jsonReceived);
        connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));

        m_clients.append(worker);//连接成功，就将该客户端放进m_clients列表中
        emit logMessage("新的用户连接上了");//有新连接就发一个消息

}



void ChatServer::broadcast(const QJsonObject &message, ServerWorker *exclude)
{
    for(ServerWorker *worker: m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::stopServer()
{
    close();//调用QTcpServer的close()
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

        broadcast(message, sender);
    }
    else if(typeVal.toString().compare("login",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("text");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        sender->setUserName(usernameVal.toString());
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
}

void ChatServer::userDisconnected(ServerWorker *sender)
{
    m_clients.removeAll(sender);//只从列表中移除sender
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
