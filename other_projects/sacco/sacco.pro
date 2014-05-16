#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T08:26:33
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

DESTDIR = ../../build

TARGET = sacco
TEMPLATE = app

INCLUDEPATH +=  . ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/qcustomplot

LIBS += -L../../build -lmanhattanstyle  -ldatapublics -lrenderer -lcommon -lcustommodels

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/\''


SOURCES += main.cpp\
        saccomainwindow.cpp

HEADERS  += saccomainwindow.h

FORMS    += saccomainwindow.ui
