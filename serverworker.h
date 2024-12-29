#ifndef SERVERWORKER_H
#define SERVERWORKER_H

#include <QObject>
#include<QTcpSocket>

class ServerWorker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWorker(QObject *parent = nullptr);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);
    QString userName();
    void setUserName(QString user);


signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWorker *sender, const QJsonObject &docObj);
    void disconnectedFromClient();

private:
    QTcpSocket *m_serverSocket;
    QString m_userName;

public slots:
    void onReadyRead();//收到消息
    void sendMessage(const QString &text, const QString &type="message");//传出去消息
    void sendJson(const QJsonObject &json);

};

#endif // SERVERWORKER_H
