#-------------------------------------------------
#
# Project created by QtCreator 2013-04-30T07:53:42
#
#-------------------------------------------------

QT += core sql
#QT       -= gui

DESTDIR += ../../build/sqldrivers
TARGET = qmysqlembeddeddriver
TEMPLATE = lib
CONFIG += qt plugin
DEFINES += MYSQLEMBEDDEDDRIVER_LIBRARY
DEFINES += QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII
INCLUDEPATH+=C:\\Qt\\sdk\\mysql\\include
#LIBS +=-L C:\\Qt\\sdk\\QtSources\\4.8.1\\src\\sql\\drivers\\mysql -lqsqlmysql4
#LIBS+=C:\\Qt\\sdk\\mysql\\lib\\mysqlserver.lib
LIBS+=C:\\Qt\\sdk\\mysql\\lib\\libmysqld.lib
#LIBS+=C:\\Qt\\sdk\\mysql\\lib\\mysqlclient.lib

SOURCES += \
    qmysqlembeddeddriver.cpp \
    main.cpp

HEADERS +=\
        mysqlembeddeddriver_global.h \
    qmysqlembeddeddriver.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
