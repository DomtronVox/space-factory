#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T16:21:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#CONFIG   += c++11
#QMAKE_CXXFLAGS += -std=c++0x
#Above lines were included as I attempted to get the program to compile on Mac

TARGET = space-factory
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    highscores.cpp \
    model.cpp \
    entities.cpp \
    builder_part.cpp \
    objectlabel.cpp \
    game_window.cpp \
    #movable_part.cpp
    movable_part.cpp \
    base_entity.cpp


HEADERS  += mainwindow.h \
    model.h \
    entities.h \
    angular_part.h \
    killable_part.h \
    weapon_part.h \
    builder_part.h \
    movable_part.h \
    objectlabel.h \
    highscores.h \
    game_window.h \
    base_entity.h


FORMS    += mainwindow.ui \
    gamewindow.ui

RESOURCES += \
    resources.qrc

