<<<<<<< HEAD
QT       += core gui network sql widgets
=======
QT       += core gui network
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatclient.cpp \
<<<<<<< HEAD
    historydialog.cpp \
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
    main.cpp \
    mainwindow.cpp

HEADERS += \
    chatclient.h \
<<<<<<< HEAD
    historydialog.h \
    mainwindow.h

FORMS += \
    historydialog.ui \
=======
    mainwindow.h

FORMS += \
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
<<<<<<< HEAD

RESOURCES += \
    image.qrc
=======
>>>>>>> 060a85a2b73e68c2889eb1f4b0c57daaef951a39
