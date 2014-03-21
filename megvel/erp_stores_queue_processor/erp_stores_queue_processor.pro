#-------------------------------------------------
#
# Project created by QtCreator 2013-08-14T10:29:57
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

DESTDIR = ../../build/
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

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

TARGET = StoreQueueProcessor
TEMPLATE = app


SOURCES += main.cpp\
        storequeuemw.cpp

HEADERS  += storequeuemw.h

FORMS    += storequeuemw.ui
