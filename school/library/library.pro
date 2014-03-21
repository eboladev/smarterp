#-------------------------------------------------
#
# Project created by QtCreator 2012-07-26T22:18:06
#
#-------------------------------------------------

QT       += core gui    sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = library
TEMPLATE = lib
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/OpenRPT/renderer ../../universal/common ../../universal/common

LIBS += -L../../lib -ldatapublics
LIBS += -L../../lib -lmanhattanstyle -lcustommodels -lrenderer -lcommon
SOURCES +=\
    libplugin.cpp \
    librarymainwindow.cpp

HEADERS  += \
    libplugin.h \
    librarymainwindow.h

FORMS    += \
    librarymainwindow.ui
