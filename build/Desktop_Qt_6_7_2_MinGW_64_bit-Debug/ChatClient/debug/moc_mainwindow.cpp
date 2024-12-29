/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../ChatClient/mainwindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_loginButton_clicked",
    "",
    "on_sayButton_clicked",
    "on_logoutButton_clicked",
    "connectedToServer",
    "messageReceived",
    "sender",
    "text",
    "jsonReceived",
    "docObj",
    "userJoined",
    "user",
    "userLeft",
    "userListReceived",
<<<<<<< HEAD
    "list",
    "createConnection",
    "on_privateSayButton_clicked",
    "on_kickButton_clicked",
    "on_userListWidget_itemDoubleClicked",
    "QListWidgetItem*",
    "item",
    "on_muteButton_clicked",
    "on_ummuteButton_clicked",
    "on_historyButton_clicked",
    "on_returnButton_clicked"
=======
    "list"
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
      17,   14, // methods
=======
       9,   14, // methods
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
<<<<<<< HEAD
       1,    0,  116,    2, 0x08,    1 /* Private */,
       3,    0,  117,    2, 0x08,    2 /* Private */,
       4,    0,  118,    2, 0x08,    3 /* Private */,
       5,    0,  119,    2, 0x08,    4 /* Private */,
       6,    2,  120,    2, 0x08,    5 /* Private */,
       9,    1,  125,    2, 0x08,    8 /* Private */,
      11,    1,  128,    2, 0x08,   10 /* Private */,
      13,    1,  131,    2, 0x08,   12 /* Private */,
      14,    1,  134,    2, 0x08,   14 /* Private */,
      16,    0,  137,    2, 0x08,   16 /* Private */,
      17,    0,  138,    2, 0x08,   17 /* Private */,
      18,    0,  139,    2, 0x08,   18 /* Private */,
      19,    1,  140,    2, 0x08,   19 /* Private */,
      22,    0,  143,    2, 0x08,   21 /* Private */,
      23,    0,  144,    2, 0x08,   22 /* Private */,
      24,    0,  145,    2, 0x08,   23 /* Private */,
      25,    0,  146,    2, 0x08,   24 /* Private */,
=======
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    2,   72,    2, 0x08,    5 /* Private */,
       9,    1,   77,    2, 0x08,    8 /* Private */,
      11,    1,   80,    2, 0x08,   10 /* Private */,
      13,    1,   83,    2, 0x08,   12 /* Private */,
      14,    1,   86,    2, 0x08,   14 /* Private */,
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QJsonObject,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QStringList,   15,
<<<<<<< HEAD
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_loginButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sayButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_logoutButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'connectedToServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'jsonReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonObject &, std::false_type>,
        // method 'userJoined'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'userLeft'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'userListReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
<<<<<<< HEAD
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'createConnection'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'on_privateSayButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_kickButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_userListWidget_itemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>,
        // method 'on_muteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ummuteButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_historyButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_returnButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
=======
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_loginButton_clicked(); break;
        case 1: _t->on_sayButton_clicked(); break;
        case 2: _t->on_logoutButton_clicked(); break;
        case 3: _t->connectedToServer(); break;
        case 4: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->jsonReceived((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1]))); break;
        case 6: _t->userJoined((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->userLeft((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->userListReceived((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
<<<<<<< HEAD
        case 9: { bool _r = _t->createConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->on_privateSayButton_clicked(); break;
        case 11: _t->on_kickButton_clicked(); break;
        case 12: _t->on_userListWidget_itemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QListWidgetItem*>>(_a[1]))); break;
        case 13: _t->on_muteButton_clicked(); break;
        case 14: _t->on_ummuteButton_clicked(); break;
        case 15: _t->on_historyButton_clicked(); break;
        case 16: _t->on_returnButton_clicked(); break;
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< HEAD
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
=======
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
    }
    return _id;
}
QT_WARNING_POP
