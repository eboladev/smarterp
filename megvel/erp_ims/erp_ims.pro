#-------------------------------------------------
#
# Project created by QtCreator 2012-09-04T19:31:12
#
#-------------------------------------------------

QT       += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TARGET = erp_ims
TEMPLATE = lib
CONFIG +=   plugin
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp


LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon


DEFINES += ERP_IMS_LIBRARY


SOURCES +=\
        imsmainwindow.cpp \
    imsplugin.cpp \
    selectfile.cpp \
    #main.cpp \
    containereditor.cpp \
    ims_mw.cpp \
    ims_suppliers.cpp \
    rvrsuppliereditor.cpp \
    ims_producteditor.cpp \
    ims_reels.cpp \
    ims_kracharges.cpp \
    ims_reellinker.cpp \
    paymentscalendar.cpp \
    tabularcontainereditor.cpp

HEADERS  += imsmainwindow.h \
    imsplugin.h \
    selectfile.h \
    containereditor.h \
    ims_mw.h \
    ims_suppliers.h \
    rvrsuppliereditor.h \
    ims_producteditor.h \
    ims_reels.h \
    ims_kracharges.h \
    ims_reellinker.h \
    paymentscalendar.h \
    tabularcontainereditor.h

FORMS    += imsmainwindow.ui \
    selectfile.ui \
    containereditor.ui \
    ims_mw.ui \
    ims_suppliers.ui \
    rvrsuppliereditor.ui \
    ims_producteditor.ui \
    ims_reels.ui \
    ims_kracharges.ui \
    ims_reellinker.ui \
    paymentscalendar.ui \
    tabularcontainereditor.ui
