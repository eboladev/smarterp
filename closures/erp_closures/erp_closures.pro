#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T14:38:47
#
#-------------------------------------------------

QT       += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TARGET = erp_closures
TEMPLATE = lib
CONFIG +=   plugin
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp


LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon
DEFINES += ERP_CLOSURES_LIBRARY

SOURCES += closuresplugin.cpp \
    closuresmainwindow.cpp \
    crm/producteditor.cpp \
    crm/lpooclinker.cpp \
    crm/purchaseorders.cpp \
    crm/customereditor.cpp \
    crm/generatejobticket.cpp \
    crm/jobticket.cpp \
    crm/newlpo.cpp \
    crm/crmmainwindow.cpp \
    crm/userdetailseditor.cpp \
    production/schedulermw.cpp \
    production/productiondataentrymw.cpp \
    production/machines.cpp \
    production/productionmw.cpp \
    production/productiondataentrywizard.cpp \
    reportpreview.cpp

HEADERS += closuresplugin.h\
        erp_closures_global.h \
    closuresmainwindow.h \
    crm/lpooclinker.h \
    crm/purchaseorders.h \
    crm/customereditor.h \
    crm/jobticket.h \
    crm/generatejobticket.h \
    crm/producteditor.h \
    crm/userdetailseditor.h \
    crm/crmmainwindow.h \
    crm/newlpo.h \
    production/schedulermw.h \
    production/productiondataentrymw.h \
    production/machines.h \
    production/productiondataentrywizard.h \
    production/productionmw.h \
    reportpreview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    closuresmainwindow.ui \
    crm/producteditor.ui \
    crm/lpooclinker.ui \
    crm/purchaseorders.ui \
    crm/generatejobticket.ui \
    crm/customereditor.ui \
    crm/crmmainwindow.ui \
    crm/userdetailseditor.ui \
    crm/newlpo.ui \
    production/schedulermw.ui \
    production/productiondataentrymw.ui \
    production/machines.ui \
    production/productiondataentrywizard.ui \
    production/productionmw.ui
