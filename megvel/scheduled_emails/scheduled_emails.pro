#-------------------------------------------------
#
# Project created by QtCreator 2013-07-16T08:07:31
#
#-------------------------------------------------

QT       += core gui sql xml

QT       -= gui

TARGET = scheduled_emails
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp


LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon



SOURCES += main.cpp \
    emaillooper.cpp

HEADERS += \
    emaillooper.h
