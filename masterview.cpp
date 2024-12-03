#include "masterview.h"
#include "ui_masterview.h"
#include<QDebug>
#include"idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    //this->setWindowFlag(Qt::FramelessWindowHint);//去掉界面最上面的边框

    goLoginView();//让首页显示登录页面

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()//转到登陆界面
{
    qDebug()<<"gologinview";
    loginview=new LoginView(this);
    pushWidgetToStackView(loginview);

    connect(loginview,SIGNAL(loginSuccess()),this,SLOT(goWelcomView()));
}

void MasterView::goWelcomView()//转到欢迎界面
{
    qDebug()<<"goWelcomView";
    welcomview=new WelcomView(this);
    pushWidgetToStackView(welcomview);

    connect(welcomview,SIGNAL(goDoctorView()),this,SLOT(goDoctorView()));
    connect(welcomview,SIGNAL(goDepartmentView()),this,SLOT(goDepartmentView()));
    connect(welcomview,SIGNAL(goPatientView()),this,SLOT(goPatientView()));
}

void MasterView::goDoctorView()//转到医生管理界面
{
    qDebug()<<"goDoctorView";
    doctorview=new DoctorView();
    pushWidgetToStackView(doctorview);

}

void MasterView::goDepartmentView()//转到科室管理界面
{
    qDebug()<<"goDepartmentView";
    departmentview=new DepartmentView();
    pushWidgetToStackView(departmentview);
}

void MasterView::goPatientView()//转到患者管理界面
{
    qDebug()<<"goPatientView";
    patientview=new PatientView();
    pushWidgetToStackView(patientview);

    connect(patientview,SIGNAL(goPatientEditView(int)),this,SLOT(goPatientEditView(int)));
}

void MasterView::goPatientEditView(int rowNo)//转到编辑患者信息界面
{
    qDebug()<<"goPatientEditView";
    patienteditview=new PatientEditView(this,rowNo);
    pushWidgetToStackView(patienteditview);

    connect(patienteditview,SIGNAL(goPreviousView()),this,SLOT(goPreviousView()));
}

void MasterView::goPreviousView()//跳转到上一个界面
{
    int count=ui->stackedWidget->count();

    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);//显示之前的页面
        ui->LabelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget=ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);//移除当前的页面
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count=ui->stackedWidget->count();//获取stackedWidget中页面的总个数
    ui->stackedWidget->setCurrentIndex(count-1);//总是显示最新加入的View
    ui->LabelTitle->setText(widget->windowTitle());//设置标题
}


void MasterView::on_btnBack_clicked()//返回
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count=ui->stackedWidget->count();
    if(count>1)
        ui->btnBack->setEnabled(true);
    else
        ui->btnBack->setEnabled(false);

    QString title=ui->stackedWidget->currentWidget()->windowTitle();

    if(title=="欢迎"){
        ui->btnBack->setEnabled(false);
        ui->btnLogout->setEnabled(true);
    }
    else{
        ui->btnLogout->setEnabled(false);
    }

    if(title=="登录"){
        ui->btnBack->setEnabled(false);
        ui->btnLogout->setEnabled(false);
    }
}


void MasterView::on_btnLogout_clicked()//注销
{
    goPreviousView();
}

