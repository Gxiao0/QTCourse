#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_chatServer=new ChatServer(this);

    connect(m_chatServer,&ChatServer::logMessage,this,&MainWindow::logMessage);
//当服务器端有日志消息（比如新用户连接等情况）时，对应的消息能传递到MainWindow中进行处理
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startStopButton_clicked()//启动/停止服务器
{
    if(m_chatServer->isListening()){//原本在监听该客户端
        m_chatServer->stopServer();
        ui->startStopButton->setText("启动服务器");
        logMessage("服务器已经停止");
    }
    else{
        if(!m_chatServer->listen(QHostAddress::Any,1967)){//启动服务器
            QMessageBox::critical(this,"错误","无法启动服务器");
            return;
        }
        logMessage("服务器已经启动");
        ui->startStopButton->setText("停止服务器");
    }

}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg);//设置文本框的内容
}

