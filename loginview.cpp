#include "loginview.h"
#include "ui_loginview.h"
#include"idatabase.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btnSignIn_clicked()//点击登录按钮
{
    QString status = IDatabase::getInstance().userLogin(ui->inputUserName->text(),ui->inputUserPassword->text());

    if(status=="loginOK")
        emit loginSuccess();
}

