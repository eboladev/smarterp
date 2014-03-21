#-------------------------------------------------
#
# Project created by QtCreator 2012-06-15T13:48:36
#
#-------------------------------------------------

QT       += sql gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TARGET = zchat
DESTDIR += ../../build/plugins
TEMPLATE = lib
CONFIG += plugin
DEFINES += ZCHAT_LIBRARY

INCLUDEPATH += ../DataPublics . ../zchat
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lrenderer -lcommon


SOURCES += zchatplugin.cpp \
    mainwindow.cpp \
    chatwindow.cpp \
    clearhistory.cpp

HEADERS += zchatplugin.h\
        zchat_global.h \
    mainwindow.h \
    chatwindow.h \
    clearhistory.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE5273E4B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = zchat.dll
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
    mainwindow.ui \
    chatwindow.ui \
    clearhistory.ui

RESOURCES += \
    res.qrc
