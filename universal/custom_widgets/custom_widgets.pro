#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T09:42:36
#
#-------------------------------------------------
QT       += sql core gui xml

DESTDIR = ../../build
TARGET = custom_widgets
##CONFIG += qt warn_on staticlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
INCLUDEPATH += ../CustomModels ../DataPublics ../common ../../common ../OpenRPT/renderer ../xlslib ../xlslib/common ../xlslib/xlslib

LIBS += -L../../build -lxlslib -ldatapublics
LIBS += -L../../build  -lrenderer  -lcommon

DEFINES += CUSTOM_WIDGETS_LIBRARY

SOURCES += customwidgets.cpp \
    reportviewwidget.cpp

HEADERS += customwidgets.h\
        custom_widgets_global.h \
    reportviewwidget.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    reportviewwidget.ui
