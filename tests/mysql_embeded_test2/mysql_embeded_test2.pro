#-------------------------------------------------
#
# Project created by QtCreator 2013-04-30T09:58:09
#
#-------------------------------------------------

QT       += core sql

QT       -= gui


DESTDIR = ../../build
TARGET = mysql_embeded_test2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../MysqlEmbeddedDriver
INCLUDEPATH+=C:\\Qt\\sdk\\mysql\\include

LIBS+=-L../../build/sqldrivers -mysqlembeddeddriver
LIBS+=C:\\Qt\\sdk\\mysql\\lib\\libmysql.lib

SOURCES += main.cpp
