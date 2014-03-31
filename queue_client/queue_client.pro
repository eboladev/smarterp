#-------------------------------------------------
#
# Project created by QtCreator 2013-11-15T12:41:39
#
#-------------------------------------------------

QT       += core gui network sql
DESTDIR = ../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = queue_client


SOURCES += main.cpp \
    queueclientdialog.cpp \
    threads/clientlistener.cpp

HEADERS += \
    queueclientdialog.h \
    threads/clientlistener.h

FORMS += \
    queueclientdialog.ui
