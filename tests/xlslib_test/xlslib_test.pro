#-------------------------------------------------
#
# Project created by QtCreator 2013-04-27T10:01:07
#
#-------------------------------------------------

QT       += core gui sql

TARGET = xlslib_test
TEMPLATE = app

DESTDIR += ../../build
LIBS += -L../../build -lxlslib
INCLUDEPATH += ../../universal/xlslib ../../universal/xlslib/common ../../universal/xlslib/xlslib ../../universal/xlslib/oledoc
SOURCES += main.cpp\
        xlsmainwindow.cpp

HEADERS  += xlsmainwindow.h

FORMS    += xlsmainwindow.ui
