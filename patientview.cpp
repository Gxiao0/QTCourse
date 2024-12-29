#include "patientview.h"
#include "ui_patientview.h"
#include"idatabase.h"

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//表示一次只能选一行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//运行后不能直接在表格编辑数据
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.patientTableModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);

    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btnAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewPatient();

    emit goPatientEditView(currow);
}


void PatientView::on_btnSearch_clicked()//查找
{
    QString filter=QString("name like '%%1%' ").arg(ui->textSearch->text());
    IDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btnDelete_clicked()//删除
{
    IDatabase::getInstance().deleteCurrentPatinet();
}


void PatientView::on_btnEdit_clicked()//修改
{
    QModelIndex curIndex=IDatabase::getInstance().thePatientSelection->currentIndex();//获取当前选择单元格的模型索引
    emit goPatientEditView(curIndex.row());
}

