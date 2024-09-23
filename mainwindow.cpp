#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::iniUI()
{
    fLabCurFile = new QLabel;
    fLabCurFile->setMidLineWidth(150);
    fLabCurFile->setText("当前文件：");
    ui->statusbar->addWidget(fLabCurFile);

    progressBar = new QProgressBar;
    progressBar -> setMinimum(5);
    progressBar -> setMaximum(50);
    progressBar->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(progressBar);


    spinFontSize = new QSpinBox;
    spinFontSize->setMaximum(50);
    spinFontSize->setMinimum(1);
    ui->toolBar->addWidget(new QLabel("字体大小"));
    ui->toolBar->addWidget(spinFontSize);
    spinFontSize->setFixedSize(70, 20);

    comboFont = new QFontComboBox;
    ui->toolBar->addWidget(new QLabel("字体"));
    ui->toolBar->addWidget(comboFont);
    comboFont->setMinimumSize(100,20);

}

void MainWindow::iniSingalSlots()
{
    connect(spinFontSize,SIGNAL(valueChanged(int)),this,
            SLOT(on_spinBoxFontSize_valueChanged(int)));
    connect(comboFont,SIGNAL(currentIndexChanged(const QString&)),this,
            SLOT(on_comboFont_currentIndexChanged(const QString&)));
    connect(dialog,SIGNAL(triggered(bool)),this,
            SLOT(on_actAbout_triggered(bool checked)));
    //connect(button,&QPushButton::clicked,this,&MainWindow::handle);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniUI();
    iniSingalSlots();
    setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    if(checked)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actCut->setEnabled(b);
    ui->actCopy->setEnabled(b);
    ui->actPaste->setEnabled(ui->textEdit->canPaste());

}


void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    ui->actItalic->setChecked(fmt.fontItalic());
    ui->actBold->setChecked(fmt.font().bold());
    ui->actUnder->setChecked(fmt.fontUnderline());

}

void MainWindow::on_spinBoxFontSize_valueChanged(int aFontSize)
{

    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar->setValue(aFontSize);
}

void MainWindow::on_comboFont_currentIndexChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}



void MainWindow::on_actAbout_triggered()
{
    QMessageBox:: StandardButton result= QMessageBox::information(NULL, "About窗口", "姓名：郭晓纯  学号：2022414040212",QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    QMessageBox::information(NULL, "OK","You click the OK!");
        // switch (result)
        // {
        //     case QMessageBox::Yes:
        //         QMessageBox::information(NULL, "YES","You click the yes !");
        //         break;
        //     case QMessageBox::No:
        //         QMessageBox::information(NULL, "No","You click the no !");
        //         break;
        //     default:
        //         break;
        // }
}

