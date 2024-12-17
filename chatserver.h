#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include<QObject>
#include "serverworker.h"

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent=nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;//客户端有连接服务器时就会自动调用该函数
    QVector<ServerWorker*> m_clients;
    void broadcast(const QJsonObject &message, ServerWorker *exclude);


signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void userDisconnected(ServerWorker *sender);

};

#endif // CHATSERVER_H
