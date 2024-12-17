#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include"loginview.h"
#include"doctorview.h"
#include"departmentview.h"
#include"patienteditview.h"
#include"patientview.h"
#include"welcomview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPatientEditView(int rowNo);
    void goPreviousView();

private slots:
    void on_btnBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btnLogout_clicked();

private:
    Ui::MasterView *ui;

    void pushWidgetToStackView(QWidget *widget);

    WelcomView *welcomview;
    DepartmentView *departmentview;
    DoctorView *doctorview;
    PatientView *patientview;
    PatientEditView *patienteditview;
    LoginView *loginview;


};
#endif // MASTERVIEW_H
