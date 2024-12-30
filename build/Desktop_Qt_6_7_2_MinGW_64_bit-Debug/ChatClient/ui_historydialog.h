/********************************************************************************
** Form generated from reading UI file 'historydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYDIALOG_H
#define UI_HISTORYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HistoryDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *searchButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *timeButton;
    QPushButton *userButton;

    void setupUi(QDialog *HistoryDialog)
    {
        if (HistoryDialog->objectName().isEmpty())
            HistoryDialog->setObjectName("HistoryDialog");
        HistoryDialog->resize(538, 417);
        verticalLayout = new QVBoxLayout(HistoryDialog);
        verticalLayout->setObjectName("verticalLayout");
        plainTextEdit = new QPlainTextEdit(HistoryDialog);
        plainTextEdit->setObjectName("plainTextEdit");

        verticalLayout->addWidget(plainTextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lineEdit = new QLineEdit(HistoryDialog);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_2->addWidget(lineEdit);

        searchButton = new QPushButton(HistoryDialog);
        searchButton->setObjectName("searchButton");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/searchByWord.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        searchButton->setIcon(icon);

        horizontalLayout_2->addWidget(searchButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        timeButton = new QPushButton(HistoryDialog);
        timeButton->setObjectName("timeButton");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/searchByRili.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        timeButton->setIcon(icon1);

        horizontalLayout->addWidget(timeButton);

        userButton = new QPushButton(HistoryDialog);
        userButton->setObjectName("userButton");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/searchByUser.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        userButton->setIcon(icon2);

        horizontalLayout->addWidget(userButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(HistoryDialog);

        QMetaObject::connectSlotsByName(HistoryDialog);
    } // setupUi

    void retranslateUi(QDialog *HistoryDialog)
    {
        HistoryDialog->setWindowTitle(QCoreApplication::translate("HistoryDialog", "Dialog", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("HistoryDialog", "\350\276\223\345\205\245\345\205\263\351\224\256\345\255\227", nullptr));
        searchButton->setText(QCoreApplication::translate("HistoryDialog", "\346\220\234\347\264\242", nullptr));
        timeButton->setText(QCoreApplication::translate("HistoryDialog", "\346\227\266\351\227\264", nullptr));
        userButton->setText(QCoreApplication::translate("HistoryDialog", "\347\224\250\346\210\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryDialog: public Ui_HistoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYDIALOG_H
