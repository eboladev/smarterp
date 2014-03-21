QT       += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TARGET = erp_ims_store
TEMPLATE = lib
CONFIG +=   plugin
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp


LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon


DEFINES += ERP_IMS_STORE_LIBRARY

HEADERS += \
    imsstoreplugin.h \
    imsstoremainwindow.h

SOURCES += \
    imsstoreplugin.cpp \
    imsstoremainwindow.cpp

FORMS += \
    imsstoremainwindow.ui
