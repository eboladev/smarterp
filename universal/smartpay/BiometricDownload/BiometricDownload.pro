#-------------------------------------------------
#
# Project created by QtCreator 2014-05-08T11:48:23
#
#-------------------------------------------------

QT       += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = BiometricDownload
TEMPLATE = app

DESTDIR = ../../../build

SOURCES += main.cpp\
        bdmainwindow.cpp \
    preferencesdialog.cpp

HEADERS  += bdmainwindow.h \
    preferencesdialog.h

FORMS    += bdmainwindow.ui \
    preferencesdialog.ui
