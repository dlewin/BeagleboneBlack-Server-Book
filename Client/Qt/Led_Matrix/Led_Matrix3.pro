#-------------------------------------------------
#
# Project created by QtCreator 2014-09-23T13:32:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Led_Matrix3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MyButtonGroup.cpp \
    ledsmatrix.cpp

HEADERS  += mainwindow.h \
    MyButtonGroup.h \
    ledsmatrix.h

FORMS    += mainwindow.ui
