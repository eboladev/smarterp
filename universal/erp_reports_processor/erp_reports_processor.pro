#-------------------------------------------------
#
# Project created by QtCreator 2012-11-16T10:31:20
#
#-------------------------------------------------

QT       += core sql network gui xml


CONFIG   += console
CONFIG   -= app_bundle

DESTDIR = ../../build
win32:TARGET = erp_reports_processor
unix:TARGET = erp_reports_processor

INCLUDEPATH +=  ../ManhattanStyle ../DataPublics ../CustomModels ../common ../OpenRPT/renderer ../ScheduledReports
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon





TEMPLATE = app


SOURCES += main.cpp \
    scheduleprocessor.cpp \
    reportmailer.cpp

HEADERS += \
    scheduleprocessor.h \
    reportmailer.h
