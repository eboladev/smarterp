#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T08:00:55
#
#-------------------------------------------------


QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
DESTDIR = ../../build/

TARGET = SmartERPUpdater
TEMPLATE = app

LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/bin
    }
    INSTALLS += target
}

SOURCES += main.cpp\
        updatermainwindow.cpp

HEADERS  += updatermainwindow.h

FORMS    += updatermainwindow.ui
