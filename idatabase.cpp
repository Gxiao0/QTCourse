#include<QUuid>
#include "idatabase.h"

void IDatabase::initDatabase()
{
//打开数据库
    database=QSqlDatabase::addDatabase("QSQLITE");//添加SQL LITE数据库驱动
    QString aFile="D:/课程/QT/实验/Lab3/lab3db.db";
    database.setDatabaseName(aFile);//设置数据库名称

    if(!database.open())
        qDebug()<<"failed to open database";
    else
        qDebug()<<"open database is ok"<<database.connectionName();
}

bool IDatabase::initPatientModel()//初始化数据表
{
    patientTableModel=new QSqlTableModel(this,database);//创建数据表
    patientTableModel->setTable("patient");//设置为数据库中的表patient
    patientTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit,OnRowChange
    patientTableModel->setSort(patientTableModel->fieldIndex("name"),Qt::AscendingOrder);//排序

    if(!patientTableModel->select()){//查询数据
        return false;
    }

    thePatientSelection=new QItemSelectionModel(patientTableModel);
    return true;
}

int IDatabase::addNewPatient()
{
    patientTableModel->insertRow(patientTableModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex=patientTableModel->index(patientTableModel->rowCount()-1,1);//创建最后一行的ModelIndex

    int curRecNo=curIndex.row();
    QSqlRecord curRec=patientTableModel->record(curRecNo);//获取当前记录
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTableModel->setRecord(curRecNo,curRec);

    qDebug()<<curRec;

    return curIndex.row();
}

bool IDatabase::searchPatient(QString filter)
{
    patientTableModel->setFilter(filter);
    return patientTableModel->select();
}

bool IDatabase::deleteCurrentPatinet()
{
    QModelIndex curIndex=thePatientSelection->currentIndex();//获取当前选中的单元格的模型索引
    patientTableModel->removeRow(curIndex.row());
    patientTableModel->submitAll();
    patientTableModel->select();
}

bool IDatabase::submitPatientEdit()
{

    return patientTableModel->submitAll();//把信息从模型传到数据库

    //qDebug() << "错误信息：" << ret<<patientTableModel->lastError().text();
    //return ret;

}

void IDatabase::revertPatientEdit()//撤销修改
{
    patientTableModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)//验证用户名和密码是否在数据库中
{
    QSqlQuery query;//查询出当前记录的所有字段
    query.prepare("select userName,password from user where userName=:USER");
    query.bindValue(":USER",userName);
    query.exec();
    qDebug()<<query.lastQuery()<<query.first();

    if(query.first() && query.value("username").isValid()){
        QString passwd=query.value("password").toString();
        if(passwd==password){
            qDebug()<<"login OK";
            return "loginOK";
        }
        else{
            qDebug()<<"wrong password";
            return "wrongPassword";
        }
    }
    else{
        qDebug()<<"no such user";
        return "wrongUsername";

    }

}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}
