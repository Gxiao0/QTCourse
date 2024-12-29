#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include<QTcpSocket>
<<<<<<< HEAD
#include <QRunnable>
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName();
    void setUserName(QString user);
<<<<<<< HEAD
    void disconnectFromClient();
    bool isAdmin();
    void setIsAdmin(bool isAdmin);
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39


signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
<<<<<<< HEAD

=======
    void disconnectedFromClient();

private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

public slots:
    void onReadyRead();//收到消息
    void sendMessage(const QString &text, const QString &type="message");//传出去消息
    void sendJson(const QJsonObject &json);

<<<<<<< HEAD
private:
    QTcpSocket *m_serverSocket;
    QString m_userName;
    bool m_isAdmin=false;//判断是否为管理员
    bool m_isMuted = false; // 新增全局禁言状态
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
};

#endif // SERVERWORKER_H
