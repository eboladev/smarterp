#-------------------------------------------------
#
# Project created by QtCreator 2012-07-17T13:06:43
#
#-------------------------------------------------

QT       += core gui xml sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = leva

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


DEFINES += LEVA_LIBRARY

SOURCES += src/main.cpp\
    src/levaplugin.cpp \
    src/levamainwindow.cpp \
    src/levaconnectionwindow.cpp \
    src/tableeditor.cpp

HEADERS  += \
    src/levaplugin.h \
    src/levamainwindow.h \
    src/levaconnectionwindow.h \
    src/tableeditor.h

FORMS    += \
    src/levamainwindow.ui \
    src/levaconnectionwindow.ui \
    src/tableeditor.ui

OTHER_FILES +=

RESOURCES += \
    ../smartpay/src/res.qrc \
    ../smartpay/src/rc.qrc \
    src/res.qrc
