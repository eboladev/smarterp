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
TARGET = erp_stores
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels


LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_STORES_LIBRARY


SOURCES += storesplugin.cpp \
    storesmainwindow.cpp \
    suppliers.cpp \
    inventory.cpp \
    inventoryeditor.cpp \
    newrequisition.cpp \
    requisitionmanager.cpp \
    postpotoquickbooks.cpp \
    requisitionwizard.cpp \
    approverequisition.cpp \
    additemtorequistion.cpp \
    newfilmrequisition.cpp \
    addartworktorequisition.cpp

HEADERS += storesplugin.h\
        erp_stores_global.h \
    storesmainwindow.h \
    suppliers.h \
    inventory.h \
    inventoryeditor.h \
    newrequisition.h \
    requisitionmanager.h \
    postpotoquickbooks.h \
    requisitionwizard.h \
    approverequisition.h \
    additemtorequistion.h \
    newfilmrequisition.h \
    addartworktorequisition.h

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

FORMS += \
    storesmainwindow.ui \
    suppliers.ui \
    inventory.ui \
    inventoryeditor.ui \
    newrequisition.ui \
    requisitionmanager.ui \
    requisitionwizard.ui \
    approverequisition.ui \
    additemtorequistion.ui \
    newfilmrequisition.ui \
    addartworktorequisition.ui
