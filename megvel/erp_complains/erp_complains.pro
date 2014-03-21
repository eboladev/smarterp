#-------------------------------------------------
#
# Project created by QtCreator 2013-01-21T11:06:16
#
#-------------------------------------------------

QT += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_complains
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += .  ../../universal/ManhattanStyle/Utils ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp ../../universal/common/tmp


LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_COMPLAINS_LIBRARY

SOURCES += \
    complainsplugin.cpp \
    erp_complains_mainwindow.cpp \
    erp_complains_editor.cpp \
    qtprinter.cpp

HEADERS +=\
        erp_complains_global.h \
    complainsplugin.h \
    erp_complains_mainwindow.h \
    erp_complains_editor.h \
    qtprinter.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE48858DD
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = erp_complains.dll
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
    erp_complains_mainwindow.ui \
    erp_complains_editor.ui
