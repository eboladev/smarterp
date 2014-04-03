#-------------------------------------------------
#
# Project created by QtCreator 2012-10-13T15:51:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui sql xml network
DESTDIR = ../../build
win32:TARGET = ErpHelper
unix:TARGET = erphelper

INCLUDEPATH +=  ../ManhattanStyle ../DataPublics ../CustomModels ../common ../OpenRPT/renderer
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon

SOURCES += main.cpp\
        helperdialog.cpp \
    settingsmanager.cpp

HEADERS  += helperdialog.h \
    settingsmanager.h

FORMS    += helperdialog.ui
