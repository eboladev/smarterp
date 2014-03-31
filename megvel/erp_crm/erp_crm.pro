#-------------------------------------------------
#
# Project created by QtCreator 2013-10-17T11:04:05
#
#-------------------------------------------------

QT       += network core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TEMPLATE = lib
CONFIG += plugin
TARGET = erp_crm
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon



DEFINES += ERP_CRM_LIBRARY

SOURCES += crmplugin.cpp \
    crmmainwindow.cpp

HEADERS += crmplugin.h\
        erp_crm_global.h \
    crmmainwindow.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    crmmainwindow.ui
