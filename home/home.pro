#-------------------------------------------------
#
# Project created by QtCreator 2012-05-13T14:40:54
#
#-------------------------------------------------
DEFINES += 'PROJECT_NAME=\'\"school\"\''
DEFINES += 'DATABASE_NAME=\'\"school\"\''

QT       += core gui sql xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
DESTDIR = ../build
win32:TARGET = SmartERP
unix:TARGET = smarterp

INCLUDEPATH +=  ../universal/ManhattanStyle ../universal/DataPublics ../universal/CustomModels ../universal/qcustomplot

LIBS += -L../build -lmanhattanstyle  -ldatapublics -lrenderer -lcommon -lcustommodels

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/\''

TEMPLATE = app
SOURCES += src/main.cpp\
        src/erpmainwindow.cpp \
    src/welcomescreen.cpp \
    src/userlogin.cpp \
    src/erp_dbsettings.cpp \
    src/updatethread.cpp

HEADERS  += src/erpmainwindow.h \
    src/welcomescreen.h \
    src/userlogin.h \
    src/erp_dbsettings.h \
    src/main.h \
    src/updatethread.h

FORMS    += src/erpmainwindow.ui \
    src/welcomescreen.ui \
    src/userlogin.ui \
    src/erp_dbsettings.ui

RESOURCES += \
    src/res.qrc

RC_FILE += \
    app.rc

OTHER_FILES += \
    app.manifest
