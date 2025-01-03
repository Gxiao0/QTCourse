#include "chatserver.h"
#include "serverworker.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>

//serverworker.cpp处理与单个客户端相关的具体通信操作

ServerWorker::ServerWorker(QObject *parent)
    : QObject{parent}
{
    m_serverSocket=new QTcpSocket(this);//创建对象，用于处理和对应的客户端进行网络数据通信
    connect(m_serverSocket,&QTcpSocket::readyRead,this,&ServerWorker::onReadyRead);//当客户端发送的数据到达并可读取时(readyRead信号被触发),就会调用onReadyRead函数来处理接收到的数据
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectFromClient);
    //connect(worker, &ServerWorker::disconnectFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker));
}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    //将传入的套接字描述符设置给内部的QTcpSocket对象
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

QString ServerWorker::userName()
{
    return m_userName;
}

void ServerWorker::setUserName(QString user)
{
    m_userName = user;
}

// void ServerWorker::disconnectFromClient()
// {
//     qDebug() << "ServerWorker::disconnectFromClient called.";
//     m_serverSocket->disconnectFromHost();
//     deleteLater(); // 确保对象被删除
// }

bool ServerWorker::isAdmin()
{
    return m_isAdmin;
}

void ServerWorker::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
}

void ServerWorker::onReadyRead()//读取客户端发送的数据
{
    QByteArray jsonData;//存放读取到的数据
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_7);

    for(;;){
        socketStream.startTransaction();//开始事务读数据
        socketStream>>jsonData;//从QDataStream中读取数据到jsonData,>>为写入数据

        if(socketStream.commitTransaction()){//事务提交成功

            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&parseError);
            if(parseError.error == QJsonParseError::NoError){
                if(jsonDoc.isObject()){
                    qDebug() << "Received JSON:" << QJsonDocument(jsonDoc).toJson();
                    emit logMessage(QJsonDocument(jsonDoc).toJson(QJsonDocument::Compact));
                    emit jsonReceived(this, jsonDoc.object());
                }
            }
        }
        else{
            break;
        }
    }

}

void ServerWorker::sendMessage(const QString &text, const QString &type)//向客户端发送消息
{
    if(m_serverSocket->state() != QAbstractSocket::ConnectedState)//先判断当前m_serverSocket的状态是否为已连接状态
        return;

    if(!text.isEmpty()){
        QDataStream serverStream(m_serverSocket);
        serverStream.setVersion(QDataStream::Qt_6_7);

        QJsonObject message;
        message["type"]=type;
        message["text"]=text;

        serverStream << QJsonDocument(message).toJson();//<<操作符将各种数据类型写入QDataStream

    }
}

void ServerWorker::sendJson(const QJsonObject &json)
{
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    emit logMessage(QLatin1String("Sending to ") + userName() + QLatin1String("-") + QString::fromUtf8(jsonData));

    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_6_2);
    socketStream << jsonData;

}
