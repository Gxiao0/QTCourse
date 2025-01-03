#include "historydialog.h"
#include "ui_historydialog.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateEdit>
#include <QInputDialog>

HistoryDialog::HistoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);
    m_searchByDate = false;

}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}


void HistoryDialog::on_searchButton_clicked(){

    QString keyword = ui->lineEdit->text().trimmed();

    if (keyword.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入搜索关键字或选择日期。");
        return;
    }

    if (m_searchByDate) {//根据日期搜索
        searchByDate(m_selectedDate);
    }
    else if (m_searchBySender) {//根据用户搜索
        searchBySender(m_selectedSender);
    }
    else {//根据关键字搜索
        searchByKeyWord(keyword);
    }
}


void HistoryDialog::on_timeButton_clicked(){
    QDate selectedDate = QDate::currentDate(); // 默认选择当前日期

    QDialog dialog(this);
    dialog.setWindowTitle("选择日期");

    QDateEdit *dateEdit = new QDateEdit(selectedDate, &dialog);
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumWidth(150); // 设置最小宽度

    QPushButton *okButton = new QPushButton("确定", &dialog);
    QPushButton *cancelButton = new QPushButton("取消", &dialog);

    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(dateEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    if (dialog.exec() == QDialog::Accepted) {
        selectedDate = dateEdit->date();
        ui->lineEdit->setText(selectedDate.toString("yyyy-MM-dd"));

        m_searchBySender=false;
        m_searchByKeyWord = false;
        m_searchByDate = true;
        m_selectedDate = selectedDate;

        qDebug() << "Selected date for search:" << m_selectedDate.toString("yyyy-MM-dd");
    }
}


void HistoryDialog::searchByDate(const QDate &date)
{
    m_searchByDate=true;
    m_searchByKeyWord=false;
    m_searchBySender=false;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT sender, message, timestamp, is_admin FROM chat_history WHERE DATE(timestamp) = :date");
    query.bindValue(":date", date);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    ui->plainTextEdit->clear();
    while (query.next()) {
        hasResults = true;
        QString sender = query.value(0).toString();
        QString message = query.value(1).toString();
        QDateTime timestamp = query.value(2).toDateTime();
        bool isAdmin = query.value(3).toBool();

        QString prefix = isAdmin ? "[管理员]" : "";
        ui->plainTextEdit->appendPlainText(timestamp.toString("yyyy-MM-dd hh:mm:ss") + " " + sender + prefix + ": " + message);
    }
    if (!hasResults) {
        ui->plainTextEdit->appendPlainText("没有找到匹配的聊天记录。");
        qDebug() << "No records found for date:" << date.toString("yyyy-MM-dd");
    }

    // 重置查询标志位
    m_searchByDate = false;
    m_searchByKeyWord = false;
    m_searchBySender = false;
}

void HistoryDialog::searchByKeyWord(const QString &keyword)
{
    m_searchByKeyWord = true;
    m_searchByDate = false;
    m_searchBySender=false;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT sender, message, timestamp, is_admin FROM chat_history WHERE message LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    ui->plainTextEdit->clear();
    hasResults = false;
    while (query.next()) {
        hasResults = true;
        QString sender = query.value(0).toString();
        QString message = query.value(1).toString();
        QDateTime timestamp = query.value(2).toDateTime();
        bool isAdmin = query.value(3).toBool();

        QString prefix = isAdmin? "[管理员]" : "";
        ui->plainTextEdit->appendPlainText(timestamp.toString("yyyy-MM-dd hh:mm:ss") + " " + sender + prefix + ": " + message);
    }
    if (!hasResults) {
        ui->plainTextEdit->appendPlainText("未找到该聊天记录");
        }

    // 重置查询标志位
    m_searchByDate = false;
    m_searchByKeyWord = false;
    m_searchBySender = false;
}

void HistoryDialog::searchBySender(const QString &sender)
{
    m_searchBySender=true;
    m_searchByDate=false;
    m_searchByKeyWord=false;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT sender, message, timestamp, is_admin FROM chat_history WHERE sender = :sender");
    query.bindValue(":sender", sender);
    qDebug() << "Executing query:" << query.lastQuery();

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    ui->plainTextEdit->clear();
    hasResults = false;
    while (query.next()) {
        hasResults = true;

        QString senderFromQuery = query.value(0).toString();
        QString message = query.value(1).toString();
        QDateTime timestamp = query.value(2).toDateTime();
        bool isAdmin = query.value(3).toBool();

        m_selectedSender=senderFromQuery;

        QString prefix = isAdmin? "[管理员]" : "";
        ui->plainTextEdit->appendPlainText(timestamp.toString("yyyy-MM-dd hh:mm:ss") + " " + senderFromQuery + prefix + ": " + message);
    }
    if (!hasResults) {
        ui->plainTextEdit->appendPlainText("未找到该聊天记录");
    }

    m_searchByDate = false;
    m_searchByKeyWord = false;
    m_searchBySender = false;

}

QStringList HistoryDialog::getAllUsernames()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT DISTINCT sender FROM chat_history");
    query.exec();

    QStringList usernames;
    while (query.next()) {
        usernames.append(query.value(0).toString());
    }
    return usernames;
}


void HistoryDialog::on_userButton_clicked()
{
    QStringList usernames = getAllUsernames();

    bool ok;
    QString selectedUser = QInputDialog::getItem(this, "选择用户", "用户名列表:", usernames, 0, false, &ok);
    if (ok && !selectedUser.isEmpty()) {
        ui->lineEdit->setText(selectedUser);

        m_selectedSender = selectedUser; // 确保设置正确的用户名
        m_searchBySender = true; // 设置标志位为按用户搜索
    }
    qDebug() << "Searching for sender:" << selectedUser;
}
