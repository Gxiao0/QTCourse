#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include<QTcpSocket>
#include <QMessageBox>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);
    bool isAdmin() const {return m_isAdmin;}
    void setAdminStatus(bool isAdmin){m_isAdmin = isAdmin;}
    void setMuted(bool muted);
    bool isMuted() const;
    bool m_isMuted = false;

signals:
    void connected();
    void messageReceived(const QString &text);
    void jsonReceived(const QJsonObject &docObj);
    void muteChat();
    void unmuteChat();

private:
    QTcpSocket *m_clientSocket;
    bool m_isAdmin = false;
    bool alreadyNotified = false;


public slots:
    void onReadyRead();//收到消息
    void sendMessage(const QString &text, const QString &type="message", const QString &target="", bool isAdmin="");//传出去消息
    void connectToServer(const QHostAddress &address, quint16 port);
    void disconnectFromHost();

};

#endif // CHATCLIENT_H
