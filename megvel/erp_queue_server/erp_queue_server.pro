#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T09:24:35
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

TARGET = erp_queue_server
TEMPLATE = app

SOURCES += main.cpp\
        queueservermainwindow.cpp \
    queueserverpreferences.cpp \
    threadedrequisitionquemanager.cpp

HEADERS  += queueservermainwindow.h \
    queueserverpreferences.h \
    threadedrequisitionquemanager.h

FORMS    += queueservermainwindow.ui \
    queueserverpreferences.ui

RESOURCES += \
    res.qrc
