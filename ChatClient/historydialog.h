#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonArray>
#include "chatclient.h"


namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_searchButton_clicked();

    void on_timeButton_clicked();
    void searchByDate(const QDate &date);
    void searchByKeyWord(const QString &keyword);
    void searchBySender(const QString &sender);
    QStringList getAllUsernames();
    void on_userButton_clicked();

signals:

private:
    Ui::HistoryDialog *ui;
    ChatClient *m_chatClient;
    bool m_searchByDate; // 标志，表示是否按日期搜索
    QDate m_selectedDate; // 保存用户选择的日期
    bool m_searchByKeyWord = false;
    bool hasResults = false;
    bool m_searchBySender=false;
    QString m_selectedSender;

};

#endif // HISTORYDIALOG_H
