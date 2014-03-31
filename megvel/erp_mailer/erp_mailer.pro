#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T11:22:22
#
#-------------------------------------------------

QT       += core sql network
DESTDIR = ../../build/
INCLUDEPATH +=  ../../universal/DataPublics .

QT       -= gui
LIBS += -L../../build -ldatapublics
TARGET = erp_mailer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mailerparent.cpp

HEADERS += \
    mailerparent.h
