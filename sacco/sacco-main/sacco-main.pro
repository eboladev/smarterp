#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T09:37:20
#
#-------------------------------------------------

QT       += core gui sql xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

win32:TARGET = SaccoMain
unix:TARGET = sacco-main
DESTDIR = ../../build
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/common ../../universal/OpenRPT/renderer

#LIBS += -L../build
LIBS += -L../../build -lmanhattanstyle -lcustommodels -lxlslib -lrenderer  -lcommon -ldatapublics


TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    members.cpp \
    companies.cpp \
    lists.cpp

HEADERS  += mainwindow.h \
    members.h \
    companies.h \
    lists.h

FORMS    += mainwindow.ui \
    members.ui \
    companies.ui \
    lists.ui

RESOURCES += \
    sacco-res.qrc
