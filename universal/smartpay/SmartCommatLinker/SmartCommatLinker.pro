#-------------------------------------------------
#
# Project created by QtCreator 2014-02-01T07:44:04
#
#-------------------------------------------------

QT += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = SmartCommatLinker
TEMPLATE = app

#INCLUDEPATH += . ../../ManhattanStyle ../../ManhattanStyle/Utils ../../common ../../OpenRPT/renderer ../../OpenRPT/common ../../common/tmp ../../../common/tmp ../../DataPublics ../../CustomModels

DESTDIR = ../../../build

SOURCES += main.cpp\
        linkermainwindow.cpp \
    settingsdialog.cpp \
    settingsmanager.cpp \
    odbctomysqlimport.cpp \
    aboutdialog.cpp

HEADERS  += linkermainwindow.h \
    settingsdialog.h \
    settingsmanager.h \
    odbctomysqlimport.h \
    aboutdialog.h

FORMS    += linkermainwindow.ui \
    settingsdialog.ui \
    aboutdialog.ui

UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

RC_FILE = linker.rc

RESOURCES += \
    res.qrc
