#-------------------------------------------------
#
# Project created by QtCreator 2012-10-06T20:23:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui sql xml network
DESTDIR = ../../build
win32:TARGET = tlm
unix:TARGET = tlm

INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/common ../../universal/OpenRPT/renderer
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon


SOURCES += main.cpp\
        tlmmainwindow.cpp \
    tlmpreferences.cpp

HEADERS  += tlmmainwindow.h \
    tlmpreferences.h

FORMS    += tlmmainwindow.ui \
    tlmpreferences.ui

RC_FILE += \
    app.rc

RESOURCES += \
    tlm_res.qrc
