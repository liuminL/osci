#-------------------------------------------------
#
# Project created by QtCreator 2018-10-14T06:54:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = osci1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xil_io.cpp \
    move.cpp

HEADERS  += mainwindow.h \
    xil_io.h \
    move.h

FORMS    += mainwindow.ui

