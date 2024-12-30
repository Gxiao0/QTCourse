#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include<QObject>
#include <QThreadPool>
#include "serverworker.h"
#include <QMutex>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class ChatServer : public QTcpServer ,public QRunnable
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent=nullptr);
    ~ChatServer();
    void run();


protected:
    void incomingConnection(qintptr socketDescriptor) override;//客户端有连接服务器时就会自动调用该函数
    QList<ServerWorker*> m_clients;
    void broadcast(const QJsonObject &message, ServerWorker *exclude);
    bool m_isMuted = false; // 新增全局禁言状态


signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void userDisconnected(ServerWorker *sender);

private:
    QThreadPool *m_pool;
    QMutex m_clientListMutex; // 互斥锁
    QSqlDatabase db;

};

#endif // CHATSERVER_H
