#-------------------------------------------------
#
# Project created by QtCreator 2012-05-27T12:20:45
#
#-------------------------------------------------

QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_production
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels  ../../universal/OpenRPT/renderer ../../universal/common ../../universal/common


LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_PRODUCTION_LIBRARY

SOURCES += productionplugin.cpp \
    productionmainwindow.cpp \
    createschedule.cpp \
    producteditoc.cpp \
    corrugatoranalysis.cpp \
    oc_reel_linking.cpp \
    wastemanagement.cpp \
    wastedataentry.cpp \
    reelallocation.cpp \
    reelallocationeditor.cpp \
    oc_reel_linking_b.cpp \
    production_reports.cpp \
    wastetabular.cpp \
    newwasteentry.cpp \
    viewschedule.cpp \
    samplecalc.cpp \
    tabularoclinking.cpp

HEADERS += productionplugin.h\
        erp_production_global.h \
    productionmainwindow.h \
    createschedule.h \
    producteditoc.h \
    corrugatoranalysis.h \
    oc_reel_linking.h \
    wastemanagement.h \
    wastedataentry.h \
    reelallocation.h \
    reelallocationeditor.h \
    oc_reel_linking_b.h \
    production_reports.h \
    wastetabular.h \
    newwasteentry.h \
    viewschedule.h \
    samplecalc.h \
    tabularoclinking.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE2BB8CFF
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = erp_production.dll
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
    productionmainwindow.ui \
    createschedule.ui \
    producteditoc.ui \
    corrugatoranalysis.ui \
    oc_reel_linking.ui \
    wastemanagement.ui \
    wastedataentry.ui \
    reelallocation.ui \
    reelallocationeditor.ui \
    oc_reel_linking_b.ui \
    production_reports.ui \
    wastetabular.ui \
    newwasteentry.ui \
    viewschedule.ui \
    samplecalc.ui \
    tabularoclinking.ui
