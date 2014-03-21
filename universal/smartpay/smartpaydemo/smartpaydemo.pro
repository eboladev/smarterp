#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T12:14:41
#
#-------------------------------------------------
QT += core gui xml sql
TEMPLATE = app
CONFIG += plugin
TARGET = smartpaydemo
#DEPENDPATH += .
include(../smartpay/smartpay.pri)
INCLUDEPATH += . ../src ../../ManhattanStyle ../../ManhattanStyle/Utils ../../common ../../OpenRPT/renderer ../../OpenRPT/common ../../common/tmp ../../../common/tmp ../../DataPublics ../../CustomModels

DESTDIR = ../../../build

LIBS += -L../../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../../build -lmanhattanstyle -lrenderer  -lcommon

INCLUDEPATH+=C:\\Qt\\sdk\\mysql\\include
LIBS+=C:\\Qt\\sdk\\mysql\\lib\\libmysqld.lib

SOURCES +=    main.cpp \
    smartpayembeddeddatabasemanager.cpp \
    importfromsql.cpp


UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

RC_FILE = SmartPay.rc

HEADERS += \
    smartpayembeddeddatabasemanager.h \
    importfromsql.h

FORMS +=

