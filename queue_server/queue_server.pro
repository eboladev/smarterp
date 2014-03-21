#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T08:22:46
#
#-------------------------------------------------

QT       += core gui sql xml network
DESTDIR = ../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = queue_server
TEMPLATE = app

INCLUDEPATH +=  ../universal/ManhattanStyle ../universal/DataPublics ../universal/CustomModels
LIBS += -L../build -lxlslib -ldatapublics -lcustommodels
LIBS += -L../build -lmanhattanstyle -lrenderer  -lcommon

SOURCES += main.cpp\
        qsmainwindow.cpp \
    pingtest.cpp \
    mailqueue.cpp

HEADERS  += qsmainwindow.h \
    pingtest.h \
    mailqueue.h

FORMS    += qsmainwindow.ui

RESOURCES += \
    queueres.qrc

RC_FILE += \
    app.rc

OTHER_FILES += \
    app.manifest
