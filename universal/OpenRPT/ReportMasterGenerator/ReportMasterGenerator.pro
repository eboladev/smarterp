#-------------------------------------------------
#
# Project created by QtCreator 2012-02-15T08:50:15
#
#-------------------------------------------------

include( ../../global.pri )

TEMPLATE = lib
TARGET = reportgenerator
QT       += core gui sql xml network
CONFIG += plugin
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
DESTDIR     = ../../../build/plugins
MOC_DIR     = tmp
UI_DIR      = tmp
OBJECTS_DIR = tmp

INCLUDEPATH += ../../common ../common ../images ../../DataPublics
LIBS += -L../../../build -lwrtembed -lcommon -lrenderer
LIBS += -L../../../build -ldatapublics

RC_FILE = writer.rc
macx:RC_FILE = ../images/OpenRPT.icns

SOURCES +=\
        mainwindow.cpp \
    autoreport.cpp \
    generatorplugin.cpp

HEADERS  += mainwindow.h \
    autoreport.h \
    reportgenerator_global.h \
    generatorplugin.h

FORMS    += mainwindow.ui \
    autoreport.ui

QT += xml sql core gui
#QT += qt3support

RESOURCES +=
