#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T07:57:46
#
#-------------------------------------------------

QT       += sql core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = app
QT       += core gui sql xml network
DESTDIR = ../../build
win32:TARGET = UpdateServer
unix:TARGET = UpdateServer

INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/common ../../universal/OpenRPT/renderer
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon

SOURCES += main.cpp\
        updateservermainwindow.cpp

HEADERS  += updateservermainwindow.h

FORMS    += updateservermainwindow.ui

RC_FILE += \
    app.rc

RESOURCES += \
    tlm_res.qrc
