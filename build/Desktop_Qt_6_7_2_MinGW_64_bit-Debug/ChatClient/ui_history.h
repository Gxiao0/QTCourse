/********************************************************************************
** Form generated from reading UI file 'history.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_H
#define UI_HISTORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_history
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *timeButton;
    QPushButton *userButton;
    QPushButton *returnButton;

    void setupUi(QWidget *history)
    {
        if (history->objectName().isEmpty())
            history->setObjectName("history");
        history->resize(400, 300);
        verticalLayout = new QVBoxLayout(history);
        verticalLayout->setObjectName("verticalLayout");
        plainTextEdit = new QPlainTextEdit(history);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        timeButton = new QPushButton(history);
        timeButton->setObjectName("timeButton");

        horizontalLayout->addWidget(timeButton);

        userButton = new QPushButton(history);
        userButton->setObjectName("userButton");

        horizontalLayout->addWidget(userButton);

        returnButton = new QPushButton(history);
        returnButton->setObjectName("returnButton");

        horizontalLayout->addWidget(returnButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(history);

        QMetaObject::connectSlotsByName(history);
    } // setupUi

    void retranslateUi(QWidget *history)
    {
        history->setWindowTitle(QCoreApplication::translate("history", "Form", nullptr));
        timeButton->setText(QCoreApplication::translate("history", "\346\227\266\351\227\264", nullptr));
        userButton->setText(QCoreApplication::translate("history", "\347\224\250\346\210\267", nullptr));
        returnButton->setText(QCoreApplication::translate("history", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class history: public Ui_history {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_H
