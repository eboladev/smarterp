#-------------------------------------------------
#
# Project created by QtCreator 2013-04-10T12:24:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../updateservice

LIBS +=-L../../build -lupdateservice

DESTDIR = ../../build
win32:TARGET = SmartLauncher
unix:TARGET = smartlauncher
TEMPLATE = app

SOURCES += main.cpp\
        launcherdialog.cpp

HEADERS  += launcherdialog.h

FORMS    += launcherdialog.ui
