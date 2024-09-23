#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QProgressBar>
#include<QLabel>
#include<QSpinBox>
#include<QFontComboBox>
#include<QDialog>
#include<QPushButton>
#include<QVBoxLayout>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *fLabCurFile;
    QProgressBar *progressBar;
    QSpinBox *spinFontSize;
    QFontComboBox *comboFont;
    QDialog *dialog;
    QVBoxLayout* layout;
    QPushButton* button;
    void iniUI();
    void iniSingalSlots();
    void handle();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actBold_triggered(bool checked);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

    void on_spinBoxFontSize_valueChanged(int aFontSize);

    void on_comboFont_currentIndexChanged(const QString &arg1);


    void on_actAbout_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
