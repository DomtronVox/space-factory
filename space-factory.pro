#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T16:21:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = space-factory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
<<<<<<< HEAD
    gamewindow.cpp
=======
    unit_tests.cpp
>>>>>>> f495a75f02772e46e2a9b82ca9e3e61450e9ad07

HEADERS  += mainwindow.h \
    model.h \
    entities.h \
    base_enity.h \
    angular_part.h \
    killable_part.h \
    weapon_part.h \
    builder_part.h \
    gamewindow.h

FORMS    += mainwindow.ui \
    gamewindow.ui

RESOURCES += \
    resources.qrc
