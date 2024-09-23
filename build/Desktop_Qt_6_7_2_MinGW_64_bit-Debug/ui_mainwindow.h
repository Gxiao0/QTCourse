/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionxin;
    QAction *actOpen;
    QAction *actOut;
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actBold;
    QAction *actItalic;
    QAction *actUnder;
    QAction *actClear;
    QAction *actAbout;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
        actionxin = new QAction(MainWindow);
        actionxin->setObjectName("actionxin");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/new2.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionxin->setIcon(icon);
        actOpen = new QAction(MainWindow);
        actOpen->setObjectName("actOpen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/open3.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actOpen->setIcon(icon1);
        actOpen->setMenuRole(QAction::MenuRole::NoRole);
        actOut = new QAction(MainWindow);
        actOut->setObjectName("actOut");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/exit.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actOut->setIcon(icon2);
        actOut->setMenuRole(QAction::MenuRole::NoRole);
        actCut = new QAction(MainWindow);
        actCut->setObjectName("actCut");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/cut.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actCut->setIcon(icon3);
        actCut->setMenuRole(QAction::MenuRole::NoRole);
        actCopy = new QAction(MainWindow);
        actCopy->setObjectName("actCopy");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/120.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actCopy->setIcon(icon4);
        actCopy->setMenuRole(QAction::MenuRole::NoRole);
        actPaste = new QAction(MainWindow);
        actPaste->setObjectName("actPaste");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/paste.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actPaste->setIcon(icon5);
        actPaste->setMenuRole(QAction::MenuRole::NoRole);
        actBold = new QAction(MainWindow);
        actBold->setObjectName("actBold");
        actBold->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/BLD.BMP"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actBold->setIcon(icon6);
        actBold->setMenuRole(QAction::MenuRole::NoRole);
        actItalic = new QAction(MainWindow);
        actItalic->setObjectName("actItalic");
        actItalic->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/ITL.BMP"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actItalic->setIcon(icon7);
        actItalic->setMenuRole(QAction::MenuRole::NoRole);
        actUnder = new QAction(MainWindow);
        actUnder->setObjectName("actUnder");
        actUnder->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/images/WORDUNDR.BMP"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actUnder->setIcon(icon8);
        actUnder->setMenuRole(QAction::MenuRole::NoRole);
        actClear = new QAction(MainWindow);
        actClear->setObjectName("actClear");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/images/103.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actClear->setIcon(icon9);
        actClear->setMenuRole(QAction::MenuRole::NoRole);
        actAbout = new QAction(MainWindow);
        actAbout->setObjectName("actAbout");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/images/430.bmp"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actAbout->setIcon(icon10);
        actAbout->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 110, 431, 161));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionxin);
        menu->addAction(actOpen);
        menu->addAction(actOut);
        menu_2->addAction(actCut);
        menu_2->addAction(actCopy);
        menu_2->addAction(actPaste);
        menu_2->addAction(actClear);
        menu_3->addAction(actBold);
        menu_3->addAction(actItalic);
        menu_3->addAction(actUnder);
        toolBar->addAction(actionxin);
        toolBar->addAction(actOpen);
        toolBar->addAction(actOut);
        toolBar->addAction(actCut);
        toolBar->addAction(actCopy);
        toolBar->addAction(actPaste);
        toolBar->addAction(actBold);
        toolBar->addAction(actItalic);
        toolBar->addAction(actUnder);
        toolBar->addAction(actClear);
        toolBar->addAction(actAbout);

        retranslateUi(MainWindow);
        QObject::connect(actOut, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(actCut, &QAction::triggered, textEdit, qOverload<>(&QTextEdit::cut));
        QObject::connect(actCopy, &QAction::triggered, textEdit, qOverload<>(&QTextEdit::copy));
        QObject::connect(actPaste, &QAction::triggered, textEdit, qOverload<>(&QTextEdit::paste));
        QObject::connect(actClear, &QAction::triggered, textEdit, qOverload<>(&QTextEdit::clear));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionxin->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#if QT_CONFIG(tooltip)
        actionxin->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        actOpen->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actOut->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(tooltip)
        actOut->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#if QT_CONFIG(tooltip)
        actCut->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_CONFIG(tooltip)
        actCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#if QT_CONFIG(tooltip)
        actCopy->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
        actPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#if QT_CONFIG(tooltip)
        actPaste->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
        actBold->setText(QCoreApplication::translate("MainWindow", "\347\262\227\344\275\223", nullptr));
#if QT_CONFIG(tooltip)
        actBold->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\227\344\275\223", nullptr));
#endif // QT_CONFIG(tooltip)
        actItalic->setText(QCoreApplication::translate("MainWindow", "\346\226\234\344\275\223", nullptr));
#if QT_CONFIG(tooltip)
        actItalic->setToolTip(QCoreApplication::translate("MainWindow", "\346\226\234\344\275\223", nullptr));
#endif // QT_CONFIG(tooltip)
        actUnder->setText(QCoreApplication::translate("MainWindow", "\344\270\213\345\210\222\347\272\277", nullptr));
#if QT_CONFIG(tooltip)
        actUnder->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        actClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
#if QT_CONFIG(tooltip)
        actClear->setToolTip(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
#endif // QT_CONFIG(tooltip)
        actAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(tooltip)
        actAbout->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#endif // QT_CONFIG(tooltip)
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\240\274\345\274\217", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
