#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T12:34:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smartpay-launcher
TEMPLATE = app


SOURCES += main.cpp\
        launcherdialog.cpp \
    userlogin.cpp

HEADERS  += launcherdialog.h \
    userlogin.h

FORMS    += launcherdialog.ui \
    userlogin.ui

RC_FILE = rc.rc
