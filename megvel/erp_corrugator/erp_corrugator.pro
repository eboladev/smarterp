#-------------------------------------------------
#
# Project created by QtCreator 2013-04-16T09:26:19
#
#-------------------------------------------------

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
DESTDIR = ../../build/
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/bin
    }
    INSTALLS += target
}

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/\''

TARGET = erp_corrugator
TEMPLATE = app


SOURCES += main.cpp\
        corrugatormw.cpp

HEADERS  += corrugatormw.h

FORMS    += corrugatormw.ui
