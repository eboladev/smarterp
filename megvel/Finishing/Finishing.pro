#-------------------------------------------------
#
# Project created by QtCreator 2012-05-22T21:08:11
#
#-------------------------------------------------



QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_production_finishing
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

LIBS += -L../../build -lcustommodels -lxlslib  -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_FINISHING_LIBRARY

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE72E0953
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = erp_qc.dll
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

HEADERS += \
    finishingplugin.h \
    finishingmainwindow.h \
    finishing_peeling.h \
    finishing_dataentry.h \
    finishing_gluing.h \
    finishing_stitching.h \
    finishing_report.h

SOURCES += \
    finishingplugin.cpp \
    finishingmainwindow.cpp \
    finishing_peeling.cpp \
    finishing_dataentry.cpp \
    finishing_gluing.cpp \
    finishing_stitching.cpp \
    finishing_report.cpp

FORMS += \
    finishingmainwindow.ui \
    finishing_peeling.ui \
    finishing_dataentry.ui \
    finishing_gluing.ui \
    finishing_stitching.ui \
    finishing_report.ui

