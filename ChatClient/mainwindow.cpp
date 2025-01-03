#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "historydialog.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->loginPage);//设置首页为登录界面
    inChatPage = false; // 初始化不在聊天界面

    m_chatClient = new ChatClient(this);
    connect(m_chatClient,&ChatClient::connected, this, &MainWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::jsonReceived, this, &MainWindow::jsonReceived);
    connect(m_chatClient, &ChatClient::muteChat, this, &MainWindow::handleMuteChat);
    connect(m_chatClient, &ChatClient::unmuteChat, this, &MainWindow::handleUnmuteChat);
    qDebug() << "muteChat signal connected.";
    qDebug() << "unmuteChat signal connected.";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()//登录按钮
{
    QString serverAddress = ui->serverEdit->text();
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    if (createConnection()) {
        QSqlQuery query;
        // 先查询管理员表
        query.prepare("SELECT * FROM administrators WHERE username =? AND password =?");
        query.addBindValue(username);
        query.addBindValue(password);
        if (query.exec() && query.next()) {

            // 是管理员，进行登录操作并设置权限标志
            m_chatClient->connectToServer(QHostAddress(serverAddress), 1967);
            // 发送包含管理员权限信息的登录消息给服务器
            m_isAdmin = true;
            m_chatClient->setAdminStatus(true);
            m_chatClient->sendMessage(username, "login", "", true);
            return;
        }

        // 如果不是管理员，查询用户表
        query.prepare("SELECT * FROM user WHERE username =? AND password =?");
        query.addBindValue(username);
        query.addBindValue(password);
        if (query.exec() && query.next()) {
            // 是普通用户，进行登录操作
            m_chatClient->connectToServer(QHostAddress(serverAddress), 1967);
            // 发送包含普通用户权限信息的登录消息给服务器
            m_isAdmin = false;
            m_chatClient->sendMessage(username, "login", "", false);
            return;
        }

        // 如果都不匹配，显示错误信息
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}


void MainWindow::on_sayButton_clicked()//发送按钮
{

    if (m_chatClient->isMuted()) { // 检查全局禁言状态
        qDebug() << "Message not sent due to mute state.";
        QMessageBox::information(this, "禁言通知", "当前处于禁言状态，无法发送消息");
        return;
    }

    if(!ui->sayLineEdit->text().isEmpty()) {
        bool isAdmin = m_isAdmin; // 根据当前用户的管理员状态传递参数
        m_chatClient->sendMessage(ui->sayLineEdit->text(), "message", "", isAdmin);

        QString sender = ui->usernameEdit->text();
        QString text = ui->sayLineEdit->text();
        if (isAdmin) {
            ui->roomTextEdit->append(QString("%1[管理员]：%2").arg(sender).arg(text));
        } else {
            ui->roomTextEdit->append(QString("%1：%2").arg(sender).arg(text));
        }
    }
    ui->sayLineEdit->clear();
}


void MainWindow::on_logoutButton_clicked()//退出按钮
{
    m_chatClient->disconnectFromHost();
    ui->stackedWidget->setCurrentWidget(ui->loginPage);//跳转到登录界面
    inChatPage = false; // 设置为不在聊天界面

    for(auto aItem : ui->userListWidget->findItems(ui->usernameEdit->text(), Qt::MatchExactly)){
        ui->userListWidget->removeItemWidget(aItem);
        delete aItem;//把用户名从列表中删除
    }
}

void MainWindow::connectedToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);//跳转到聊天界面
    inChatPage = true; // 设置为在聊天界面
    m_chatClient->sendMessage(ui->usernameEdit->text(),"login");

    // 设置privateTargetComboBox默认不选择任何用户
    ui->privateTargetComboBox->setCurrentIndex(-1);
}

void MainWindow::messageReceived(const QString &sender, const QString &text)
{
    ui->roomTextEdit->append(QString("%1 : %2").arg(sender).arg(text));
}

void MainWindow::jsonReceived(const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if(typeVal.isNull() || !typeVal.isString())
        return;

    if(typeVal.toString().compare("message",Qt::CaseInsensitive) == 0){

        const QJsonValue textVal =docObj.value("text");
        const QJsonValue senderVal = docObj.value("sender");

        if(textVal.isNull() || !textVal.isString())
            return;
        if(senderVal.isNull() || !senderVal.isString())
            return;

        QString sender = senderVal.toString();
        QString text = textVal.toString();
        // 如果发送者是管理员，修改消息格式
        if(sender!=ui->usernameEdit->text()){
            if (docObj.contains("is_admin") && docObj.value("is_admin").toBool()&& typeVal.toString() == "message") {
                m_chatClient->setAdminStatus(true);
                ui->roomTextEdit->append(QString("%1[管理员]：%2").arg(sender).arg(text));

            } else {
                ui->roomTextEdit->append(QString("%1：%2").arg(sender).arg(text));
            }
        }
        ui->roomTextEdit->update();
    }
    else if(typeVal.toString().compare("private",Qt::CaseInsensitive) == 0){
        const QJsonValue senderVal = docObj.value("sender");
        const QJsonValue textVal = docObj.value("text");
        if(senderVal.isNull() ||!senderVal.isString())
            return;
        if(textVal.isNull() ||!textVal.isString())
            return;

        QString sender = senderVal.toString();
        QString text = textVal.toString();
        // 如果发送者是管理员，修改消息格式
        bool isAdmin = docObj.contains("is_admin") && docObj.value("is_admin").toBool();
        if(isAdmin){
            ui->roomTextEdit->append(QString("%1[管理员]（私聊我）：%2").arg(sender).arg(text));
        } else {
            ui->roomTextEdit->append(QString("%1（私聊我）：%2").arg(sender).arg(text));
        }
        ui->roomTextEdit->update();
    }
    else if(typeVal.toString().compare("newuser",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("username");

        bool isMuted = docObj["is_muted"].toBool();

        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        userJoined(usernameVal.toString());

        if(isMuted){
            m_chatClient->setMuted(true);

        }
    }
    else if(typeVal.toString().compare("userdisconnected",Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("username");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        QString username = usernameVal.toString();
        userLeft(username);
    }
    else if(typeVal.toString().compare("userlist",Qt::CaseInsensitive) == 0){

        const QJsonValue userlistVal = docObj.value("userlist");
        if(userlistVal.isNull() || !userlistVal.isArray())
            return;

        userListReceived(userlistVal.toVariant().toStringList());
    }
    else if(typeVal.toString().compare("userKicked", Qt::CaseInsensitive) == 0){
        const QJsonValue usernameVal = docObj.value("username");
        if(usernameVal.isNull() || !usernameVal.isString())
            return;

        QString username = usernameVal.toString();
        // 从 privateTargetComboBox 中移除被踢出的用户
        int index = ui->privateTargetComboBox->findText(username);
        if (index != -1) {
            ui->privateTargetComboBox->removeItem(index);
        }

        // 如果被踢出的是当前用户，断开连接并返回登录界面
        if(username == ui->usernameEdit->text() && inChatPage){

            QMessageBox::warning(this, "被踢出", "您已被管理员踢出聊天室。");
            m_chatClient->disconnectFromHost();
            ui->stackedWidget->setCurrentWidget(ui->loginPage);
            inChatPage = false;
            ui->roomTextEdit->append(QString("%1已被管理员踢出群聊").arg(username));
        }else {
            // 如果不是被踢出的用户，从用户列表中移除被踢出用户
            ui->roomTextEdit->append(QString("%1已被管理员踢出群聊").arg(username));
            userLeft(username);
        }
        //return;
    }
    else if(typeVal.toString().compare("mute", Qt::CaseInsensitive) == 0){
        qDebug() << "MainWindow received mute message.";
        m_chatClient->setMuted(true);
        handleMuteChat();
    }
    else if(typeVal.toString().compare("unmute", Qt::CaseInsensitive) == 0){
        qDebug() << "MainWindow received unmute message.";
        m_chatClient->setMuted(false);
        handleUnmuteChat();

    }

}

void MainWindow::userJoined(const QString &user)
{
    ui->userListWidget->addItem(user);
    ui->privateTargetComboBox->addItem(user);
}

void MainWindow::userLeft(const QString &user)
{
    for(auto aItem : ui->userListWidget->findItems(user, Qt::MatchExactly)){
        ui->userListWidget->removeItemWidget(aItem);
        delete aItem;//把用户名从列表中删除
    }
    // 用户离开时，从ComboBox选项中移除
    int index = ui->privateTargetComboBox->findText(user);
    if (index!= -1) {
        ui->privateTargetComboBox->removeItem(index);
    }
    // 用户列表界面刷新
    ui->userListWidget->update();
}

void MainWindow::userListReceived(const QStringList &list)
{
    userListUpdating = true;
    ui->userListWidget->clear();
    ui->userListWidget->addItems(list);

    // 清空ComboBox原有选项并添加新的用户列表选项
    ui->privateTargetComboBox->clear();
    ui->privateTargetComboBox->addItems(list);
    ui->privateTargetComboBox->setCurrentIndex(-1);// 确保privateTargetComboBox默认不选择任何用户
    userListUpdating = false;
}

bool MainWindow::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="D:/课程/QT/实验/大作业/qtExperiment.db";
    db.setDatabaseName(aFile);//设置数据库名称

    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}


void MainWindow::on_privateSayButton_clicked()//私聊按钮
{
    if (m_chatClient->isMuted()) {
        qDebug() << "Message not sent due to mute state.";
        QMessageBox::information(this, "禁言通知", "当前处于禁言状态，无法发送消息");
        return;
    }

    QString text = ui->sayLineEdit->text();
    if(text.isEmpty())
        return;

    QString selectedTarget = ui->privateTargetComboBox->currentText();
    bool isAdmin = m_isAdmin && !selectedTarget.isEmpty(); // 根据当前用户的管理员状态传递参数

    if (selectedTarget.isEmpty()) {
        // 如果没有选择私聊对象，发送公开消息
        m_chatClient->sendMessage(text, "message", "", m_isAdmin);
    } else {
        // 如果选择了私聊对象，发送私聊消息
        m_chatClient->sendMessage(text, "private", selectedTarget,isAdmin);
            // 将发送的私聊消息显示在自己的聊天界面
        ui->roomTextEdit->append(QString("(我私聊%1) : %2").arg(selectedTarget).arg(text));
    }
}


void MainWindow::on_kickButton_clicked()//踢出按钮
{
    // 获取当前选中的用户
    QListWidgetItem *currentItem = ui->userListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "错误", "请选择一个用户进行踢出操作！");
        return;
    }

    if (!m_isAdmin) {
        QMessageBox::warning(this, "权限不足", "您没有权限执行踢出操作");
        return;
    }

    QString selectedUser = currentItem->text();
    if (!selectedUser.isEmpty()) {
        // 发送踢出指令给服务器，这里假设"kick"是踢出指令类型
        m_chatClient->sendMessage("", "kick", selectedUser, m_isAdmin);

        // 从本地用户列表中移除被踢用户
        for (auto aItem : ui->userListWidget->findItems(selectedUser, Qt::MatchExactly)) {
            ui->userListWidget->removeItemWidget(aItem);
            delete aItem;
        }

        // 从privateTargetComboBox中移除被踢用户
        int index = ui->privateTargetComboBox->findText(selectedUser);
        if (index!= -1) {
            ui->privateTargetComboBox->removeItem(index);
        }
    }
}


void MainWindow::on_userListWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QString selectedUser = item->text();
    ui->privateTargetComboBox->setCurrentText(selectedUser);
}


void MainWindow::on_muteButton_clicked()
{
    if (!m_isAdmin) {
        QMessageBox::warning(this, "权限不足", "您没有权限执行禁言操作");
        return;
    }

    qDebug() << "Mute button clicked";
    ui->muteButton->setEnabled(false); // 禁用按钮

    m_chatClient->setMuted(true);
    //m_chatClient->m_isMuted = true;
    qDebug() << "Set muted to true";
    m_chatClient->sendMessage("", "mute", "", true);
    qDebug() << "Sent mute message to server";
    //QMessageBox::information(this, "禁言通知", "管理员开启禁言");
    // 操作完成后重新启用按钮
    ui->muteButton->setEnabled(true);
}


void MainWindow::on_ummuteButton_clicked()
{
    if (!m_isAdmin) {
        QMessageBox::warning(this, "权限不足", "您没有权限执行此操作");
        return;
    }

    qDebug() << "Unmute button clicked";
    m_chatClient->setMuted(false);
    //m_chatClient->m_isMuted = false;

    qDebug() << "Set muted to false";
    m_chatClient->sendMessage("", "unmute", "", false);
    qDebug() << "Sent unmute message to server";

    QMessageBox::information(this, "解除禁言通知", "管理员解除禁言");
    ui->muteButton->setEnabled(true); // 重新启用按钮
}

void MainWindow::on_historyButton_clicked()
{
    historyDialog = new HistoryDialog(this);
    ui->stackedWidget->addWidget(historyDialog);
    int count=ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);
    //ui->stackedWidget->setCurrentWidget(historyDialog);
}


void MainWindow::on_returnButton_clicked()
{
    // 获取当前显示的页面
    QWidget* currentPage = ui->stackedWidget->currentWidget();

    // 检查当前页面是否为 loginPage 或 chatPage
    if (currentPage == ui->loginPage || currentPage == ui->chatPage) {
        // 如果是，则不执行任何操作，按钮无效
        return;
    }

    ui->stackedWidget->setCurrentWidget(ui->chatPage);
}

void MainWindow::handleMuteChat()
{
    QMessageBox::information(this, "禁言通知", "管理员开启禁言");
    ui->sayButton->setEnabled(false);
    ui->privateSayButton->setEnabled(false);
}

void MainWindow::handleUnmuteChat()
{
    QMessageBox::information(this, "解除禁言通知", "管理员解除禁言");
    ui->sayButton->setEnabled(true);
    ui->privateSayButton->setEnabled(true);
}

