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
    unit_tests.cpp

HEADERS  += mainwindow.h \
    model.h \
    entities.h \
    base_enity.h \
    angular_part.h \
    killable_part.h \
    weapon_part.h \
    builder_part.h \
    movable_part.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
