#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T08:25:03
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

DESTDIR = ../../../build

TEMPLATE = app

win32:TARGET = SA-Main
unix:TARGET = sa-main

INCLUDEPATH +=  . ../../../universal/ManhattanStyle ../../../universal/DataPublics ../../../universal/CustomModels ../../../universal/qcustomplot

LIBS += -L../../../build -lmanhattanstyle  -ldatapublics -lrenderer -lcommon -lcustommodels

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/\''

SOURCES += main.cpp\
        samainwindow.cpp \
    memberdetails.cpp

HEADERS  += samainwindow.h \
    memberdetails.h

FORMS    += samainwindow.ui \
    memberdetails.ui

win32:RC_FILE = sa-main.rc

OTHER_FILES += \
    app.manifest

RESOURCES += \
    sacco-res.qrc
