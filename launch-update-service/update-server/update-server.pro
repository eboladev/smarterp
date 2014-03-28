#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T13:51:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui sql xml network
DESTDIR = ../../build
TEMPLATE = app
win32:TARGET = UpdateServer
unix:TARGET = updateserver

INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/common ../../universal/OpenRPT/renderer
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon

RC_FILE += \
    app.rc

RESOURCES += \
    tlm_res.qrc


SOURCES += main.cpp\
        usmainwindow.cpp

HEADERS  += usmainwindow.h

FORMS    += usmainwindow.ui
