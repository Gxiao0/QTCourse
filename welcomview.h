#ifndef WELCOMVIEW_H
#define WELCOMVIEW_H

#include <QWidget>

namespace Ui {
class WelcomView;
}

class WelcomView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomView(QWidget *parent = nullptr);
    ~WelcomView();

private slots:
    void on_btnDepartment_clicked();

    void on_btnDoctor_clicked();

    void on_btnPatient_clicked();

signals:
    void goDepartmentView();
    void goDoctorView();
    void goPatientView();

private:
    Ui::WelcomView *ui;
};

#endif // WELCOMVIEW_H
