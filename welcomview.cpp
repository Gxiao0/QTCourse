#include "welcomview.h"
#include "ui_welcomview.h"
#include<QDebug>

WelcomView::WelcomView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomView)
{
    qDebug()<<"create WelcomView";
    ui->setupUi(this);
}

WelcomView::~WelcomView()
{
    qDebug()<<"destroy WelcoView";
    delete ui;
}

void WelcomView::on_btnDepartment_clicked()
{
    emit goDepartmentView();
}


void WelcomView::on_btnDoctor_clicked()//信号
{
    emit goDoctorView();
}


void WelcomView::on_btnPatient_clicked()
{
    emit goPatientView();
}

