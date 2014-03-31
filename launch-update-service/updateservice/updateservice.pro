#-------------------------------------------------
#
# Project created by QtCreator 2013-04-12T10:18:53
#
#-------------------------------------------------

QT       += sql network

QT       -= gui

DESTDIR = ../../build

TARGET = updateservice
TEMPLATE = lib

DEFINES += UPDATESERVICE_LIBRARY

SOURCES += updateservice.cpp \
    server.cpp

HEADERS += updateservice.h\
        updateservice_global.h \
    server.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
