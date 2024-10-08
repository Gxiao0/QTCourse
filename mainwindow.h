#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QStack>
#include<QKeyEvent>
#include <QMainWindow>
#include<QMap>
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;//操作数
    QString opcode;//操作符
    QStack<QString> operands;//存放操作数的栈
    QStack<QString>opcodes;//存放操作符的栈
    QMap<int,QPushButton*> btnNums;

    QString calculation(bool *ok=NULL);

private slots:
    void btnNumclicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_btnPoint_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();

    void on_btnEqual_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

    void on_pushButton_21_clicked();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
