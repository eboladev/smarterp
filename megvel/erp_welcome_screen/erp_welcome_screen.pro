#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T08:47:29
#
#-------------------------------------------------

QT       += core gui sql

TARGET = erp_welcome_screen
TEMPLATE = lib
CONFIG += plugin static
DESTDIR = ../lib

INCLUDEPATH += ../MegvelERP/src

SOURCES +=\
        erpwelcomescreen.cpp \
    welcomescreenplugin.cpp

HEADERS  += erpwelcomescreen.h \
    welcomescreenplugin.h

FORMS    += erpwelcomescreen.ui
