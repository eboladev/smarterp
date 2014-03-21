#-------------------------------------------------
#
# Project created by QtCreator 2013-08-16T09:21:33
#
#-------------------------------------------------
QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_stores_artworks
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels


LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERPARTWORKS_LIBRARY

SOURCES += \
    artworksplugin.cpp \
    artworksmainwindow.cpp \
    newartworkwizard.cpp \
    artworklist.cpp

HEADERS +=\
        erp-artworks_global.h \
    artworksplugin.h \
    artworksmainwindow.h \
    newartworkwizard.h \
    artworklist.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    artworksmainwindow.ui \
    newartworkwizard.ui \
    artworklist.ui
