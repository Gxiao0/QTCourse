#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums ={{Qt::Key_0,ui->btnNum0},
             {Qt::Key_1,ui->btnNum1},
             {Qt::Key_2,ui->btnNum2},
             {Qt::Key_3,ui->btnNum3},
             {Qt::Key_4,ui->btnNum4},
             {Qt::Key_5,ui->btnNum5},
             {Qt::Key_6,ui->btnNum6},
             {Qt::Key_7,ui->btnNum7},
             {Qt::Key_8,ui->btnNum8},
             {Qt::Key_9,ui->btnNum9}};


    foreach(auto btn,btnNums )
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumclicked()));

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumclicked()));

    QPushButton* btnSymbols[] = {ui->btnPlus, ui->btnMinus, ui->btnMultiple, ui->btnDivide};
    for (QPushButton* button : btnSymbols) {
        connect(button, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
    }

    //connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    //connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    //connect(ui->btnMultiple,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    //connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    btnSymbols[0] = ui->btnPercentage;
    btnSymbols[1] = ui->btnSqrt;
    btnSymbols[2] = ui->btnInverse;
    btnSymbols[3] = ui->btnSquare;
    for (QPushButton* button : btnSymbols) {
        connect(button, SIGNAL(clicked()), this, SLOT(btnUnaryOperatorClicked()));
    }

    //connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    //connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    //connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    //connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result=0;
    if(operands.size() == 2 && opcodes.size()>0){
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();//从操作数栈中将操作数取出
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op=opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result=operand1 + operand2;
        }
        else if(op == "-"){
            result=operand1 - operand2;
        }
        else if(op == "×"){
            result=operand1 * operand2;
        }
        else if(op == "÷"){
            result=operand1 / operand2;
        }

        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("calculation is in progress: operands is %1, opcode id %2")
                                   .arg(operands.size()).arg(opcodes.size()));
    }
    else
        ui->statusbar->showMessage(QString("operands is %1, opcode id %2").
                                   arg(operands.size()).arg(opcodes.size()));

    return QString::number(result);
}



void MainWindow::btnNumclicked()//双操作数字键
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if(digit == "0"  && operand == "0")
        digit = "";

    if(operand =="0" && digit !="0")
        operand = "";//operand保存第一个数字，digit保存第二个数字

    operand += digit;

    ui->display->setText(operand);
}


void MainWindow::on_btnPoint_clicked()//小数点操作符
{
    if(!operand.contains("."))//一个数字只能有一个小数点，此条件判断text中是否没有小数点
        operand += qobject_cast<QPushButton*>(sender())->text();

    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()//删除键操作符
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()//C键
{
    //operand.clear();
    //ui->display->setText(operand);

    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()//双操作符.当点击操作符后，让显示框里的操作数清空
{
    ui->statusbar->showMessage("last operand" + operand);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    //qDebug()<<opcode;

    if(operand != ""){
        operands.push_back(operand);
        operand = "";

        opcodes.push_back(opcode);

        QString result=calculation();

        ui->display->setText(result);
    }
}

void MainWindow::btnUnaryOperatorClicked()//单操作符
{
    if(operand != ""){
        double result = operand.toDouble();
        operand = "";

        QString op= qobject_cast<QPushButton*>(sender())->text();

        if(op == "%")
            result /= 100.0;
        else if(op == "1/x")
            result = 1/result;
        else if(op == "x^2")
            result *= result;
        else if(op == "√")
            result = sqrt(result);

        ui->display->setText(QString::number(result));
    }
}

void MainWindow::on_btnEqual_clicked()//等于号的操作
{
    if(operand != ""){
        operands.push_back(operand);
        operand = "";
    }

    QString result=calculation();
    ui->display->setText(result);

}

void MainWindow::keyPressEvent(QKeyEvent *event)//键盘事件处理
{
    foreach (auto btnKey, btnNums.keys()) {
        if(event->key() == btnKey)
            btnNums[btnKey]->animateClick();
    }

}

void MainWindow::on_pushButton_21_clicked()//正负号操作符
{
    if (operand!= "") {
            double value = operand.toDouble();
            operand = QString::number(-value);
            ui->display->setText(operand);
        }
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

