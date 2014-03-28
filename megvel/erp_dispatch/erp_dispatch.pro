#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T09:45:16
#
#-------------------------------------------------

QT       += network sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = erp_dispatch
TEMPLATE = lib
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += . ../../universal/common ../../universal/openrpt/common ../../universal/openrpt/renderer

LIBS += -L../../build -lmanhattanstyle -lcustommodels -ldatapublics -lrenderer -lcommon
LIBS += -L../../build  -lcustommodels -lxlslib

DEFINES += ERP_DISPATCH_LIBRARY

SOURCES += dispatchplugin.cpp \
    dispatchmainwindow.cpp \
    dispatchlistdialog.cpp \
    confirmdelivery.cpp \
    newdispatchdialog.cpp \
    pastentriesdialog.cpp

HEADERS += dispatchplugin.h\
        erp_dispatch_global.h \
    dispatchmainwindow.h \
    dispatchlistdialog.h \
    confirmdelivery.h \
    newdispatchdialog.h \
    pastentriesdialog.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    dispatchmainwindow.ui \
    dispatchlistdialog.ui \
    confirmdelivery.ui \
    newdispatchdialog.ui \
    pastentriesdialog.ui

RESOURCES += \
    dispatch_res.qrc
