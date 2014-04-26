#-------------------------------------------------
#
# Project created by QtCreator 2012-02-12T10:21:52
#
#-------------------------------------------------

DEFINES += REPORTMASTER_LIBRARY

#INCLUDEPATH += ../common ../../common ../OpenRPT/renderer . ../OpenRPT/common ../DataPublics ../common/tmp ../../common/tmp
QT       += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = reportmaster
#CONFIG += qt warn_on staticlib
DESTDIR = ../../build/plugins
MOC_DIR = tmp
UI_DIR = tmp
OBJECTS_DIR = tmp

#LIBS += -L../../build -lrenderer -lcommon
#LIBS += -L../../build -ldatapublics
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../common ../../common ../OpenRPT/renderer . ../OpenRPT/common   ../common/tmp ../../common/tmp


#INCLUDEPATH += . ./src src ../ManhattanStyle ../ManhattanStyle/Utils ../common ../OpenRPT/renderer ../OpenRPT/common ../common/tmp ../../common/tmp ../DataPublics ../CustomModels

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

SOURCES +=\
        src/mainwindow.cpp \
    src/selectreport.cpp \
    src/selectdaterange.cpp \
    src/reportmasterplugin.cpp \
    src/loadreportfromsql.cpp

HEADERS  += src/mainwindow.h \
    src/selectreport.h \
    src/selectdaterange.h \
    src/reportmaster_global.h \
    src/reportmasterplugin.h \
    src/loadreportfromsql.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0DDEA86
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = reportmaster.dll
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


FORMS    += src/mainwindow.ui \
    src/selectreport.ui \
    src/selectdaterange.ui \
    src/loadreportfromsql.ui

RESOURCES += \
    src/res.qrc
