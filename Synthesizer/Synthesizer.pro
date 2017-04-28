#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T13:32:04
#
#-------------------------------------------------

QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Synthesizer
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    functions.cpp

HEADERS  += mainwindow.h \
    functions.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    images.qrc
