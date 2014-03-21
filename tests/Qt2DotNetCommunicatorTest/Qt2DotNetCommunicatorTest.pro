#-------------------------------------------------
#
# Project created by QtCreator 2013-07-09T11:50:47
#
#-------------------------------------------------

QT       += core gui network
DESTDIR = ../../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt2DotNetCommunicatorTest
TEMPLATE = app


SOURCES += main.cpp\
        testmainwindow.cpp \
    lgmclientclass.cpp

HEADERS  += testmainwindow.h \
    lgmclientclass.h

FORMS    += testmainwindow.ui
