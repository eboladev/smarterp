#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T08:11:55
#
#-------------------------------------------------

QT       += core network gui sql xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

DESTDIR = ../../build

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/\''
INCLUDEPATH +=  . ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
LIBS += -L../../build  -ldatapublics -lcustommodels -lxlslib
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon
TARGET = mass-mailer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
