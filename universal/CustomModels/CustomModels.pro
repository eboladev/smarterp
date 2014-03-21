#-------------------------------------------------
#
# Project created by QtCreator 2012-05-22T20:48:17
#
#-------------------------------------------------

QT       += sql core gui xml

DESTDIR = ../../build
TARGET = custommodels
#CONFIG += qt warn_on staticlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
INCLUDEPATH += ../DataPublics ../common ../../common ../OpenRPT/renderer ../xlslib ../xlslib/common ../xlslib/xlslib


LIBS += -L../../build  -lrenderer  -lcommon
LIBS += -L../../build -lxlslib -ldatapublics

include(../qtxlsx/src/xlsx/qtxlsx.pri)

DEFINES += CUSTOMMODELS_LIBRARY
SOURCES += \
    customqueryview.cpp \
    htmlreportpreview.cpp \
    htmlprinter.cpp \
    html_printer.cpp \
    excelexporter.cpp \
    excelexporter_thread.cpp \
    sqlmodels.cpp

HEADERS +=\
        CustomModels_global.h \
    customqueryview.h \
    htmlreportpreview.h \
    htmlprinter.h \
    html_printer.h \
    excelexporter.h \
    excelexporter_thread.h \
    sqlmodels.h \
    sqlmodels.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE75B73A7
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CustomModels.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    customqueryview.ui \
    htmlreportpreview.ui
