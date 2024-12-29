<<<<<<< HEAD
#include "chatserver.h"
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
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
<<<<<<< HEAD
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectFromClient);
=======
    connect(m_serverSocket, &QTcpSocket::disconnected, this, &ServerWorker::disconnectedFromClient);
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

}

bool ServerWorker::setSocketDescriptor(qintptr socketDescriptor)
{
    //将传入的套接字描述符设置给内部的QTcpSocket对象
<<<<<<< HEAD
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

=======
        return m_serverSocket->setSocketDescriptor(socketDescriptor);
}



>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
QString ServerWorker::userName()
{
    return m_userName;
}

void ServerWorker::setUserName(QString user)
{
    m_userName = user;
}

<<<<<<< HEAD
void ServerWorker::disconnectFromClient()
{
    qDebug() << "ServerWorker::disconnectFromClient called.";
    m_serverSocket->disconnectFromHost();
    deleteLater(); // 确保对象被删除
}

bool ServerWorker::isAdmin()
{
    return m_isAdmin;
}

void ServerWorker::setIsAdmin(bool isAdmin)
{
    m_isAdmin = isAdmin;
}

=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
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
                    emit logMessage(QJsonDocument(jsonDoc).toJson(QJsonDocument::Compact));
                    emit jsonReceived(this, jsonDoc.object());
                }
            }
<<<<<<< HEAD

            if (jsonDoc["type"] == "mute") {
                            m_isMuted = true; // 设置当前用户的禁言状态
                            // Optional: Мaybe notify the user about the mute if necessary
                        } else if (jsonDoc["type"] == "unmute") {
                            m_isMuted = false; // 设置当前用户的解除禁言状态
                        }

=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
        }
        else{
            break;
        }
    }
<<<<<<< HEAD

=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
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
<<<<<<< HEAD


    if (json["type"].toString() == "mute") {
            // 禁言状态下不发送消息
        return;
    }
    if (json["type"].toString() == "unmute") {
            // 解除禁言后可以发送消息
        return;
    }
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
}
