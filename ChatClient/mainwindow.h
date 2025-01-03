#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatclient.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QListWidgetItem>
#include "historydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool m_isAdmin = false;

private slots:
    void on_loginButton_clicked();
    void on_sayButton_clicked();
    void on_logoutButton_clicked();
    void connectedToServer();
    void messageReceived(const QString &sender, const QString &text);
    void jsonReceived(const QJsonObject &docObj);
    void userJoined(const QString &user);
    void userLeft(const QString &user);
    void userListReceived(const QStringList &list);
    bool createConnection();
    void on_privateSayButton_clicked();
    void on_kickButton_clicked();
    void on_userListWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_muteButton_clicked();
    void on_ummuteButton_clicked();
    void on_historyButton_clicked();
    void on_returnButton_clicked();
    void handleMuteChat();
    void handleUnmuteChat();

private:
    Ui::MainWindow *ui;

    ChatClient *m_chatClient;
    bool inChatPage; //记录是否在聊天界面
    bool userListUpdating; // 新增标志位
    HistoryDialog *historyDialog;

};
#endif // MAINWINDOW_H
