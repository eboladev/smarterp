#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T12:14:41
#
#-------------------------------------------------
QT += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = app
#CONFIG += plugin
TARGET = SmartPay
#DEPENDPATH += .
include(smartpay.pri)
include(../../qtxlsx/src/xlsx/qtxlsx.pri)

INCLUDEPATH += . src ../../ManhattanStyle ../../ManhattanStyle/Utils ../../common ../../OpenRPT/renderer ../../OpenRPT/common ../../common/tmp ../../../common/tmp ../../DataPublics ../../CustomModels
INCLUDEPATH += ../src
DESTDIR = ../../../build

LIBS += -L../../../build -lxlslib
LIBS += -L../../../build -lcustom_widgets -lmanhattanstyle -lrenderer  -lcommon -lqcustomplot
LIBS += -L../../../build -ldatapublics -lcustommodels

SOURCES +=    main.cpp


UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

RC_FILE = SmartPay.rc

