#-------------------------------------------------
#
# Project created by QtCreator 2012-05-22T20:48:17
#
#-------------------------------------------------

QT       += sql core gui
DESTDIR = ../../lib
TARGET = custommodels
CONFIG += qt warn_on staticlib
TEMPLATE = lib
INCLUDEPATH += ../DataPublics
LIBS += -L ../../lib -ldatapublics
DEFINES += MAKELIB

SOURCES += \
    customqueryview.cpp

HEADERS +=\
        CustomModels_global.h \
    customqueryview.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE75B73A7
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = CustomModels.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    customqueryview.ui
