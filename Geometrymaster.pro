#-------------------------------------------------
#
# Project created by QtCreator 2020-12-03T22:09:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gometrymaster
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    mainscene.cpp \
    role.cpp \
    gun.cpp \
    bullet.cpp \
    bomb.cpp \
    dialog.cpp \
    monster1.cpp \
    button.cpp \
    exit.cpp \
    monster3.cpp \
    monster2.cpp \
    sight.cpp

HEADERS += \
        widget.h \
    mainscene.h \
    config.h \
    role.h \
    gun.h \
    bullet.h \
    bomb.h \
    dialog.h \
    monster1.h \
    button.h \
    exit.h \
    monster3.h \
    monster2.h \
    sight.h \
    function.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
