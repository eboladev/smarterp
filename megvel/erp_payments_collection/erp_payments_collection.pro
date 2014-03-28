#-------------------------------------------------
#
# Project created by QtCreator 2012-12-19T09:58:12
#
#-------------------------------------------------
QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TEMPLATE = lib
CONFIG += plugin
TARGET = erp_payments_collection
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_COLLECTION_LIBRARY

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


SOURCES += collectionplugin.cpp \
    collectionmainwindow.cpp \
    col_customerlist.cpp \
    col_invoicelist.cpp \
    col_localinvoices.cpp \
    col_invoicefetcher.cpp \
    col_threadedinvoicefetcher.cpp \
    col_ageing.cpp \
    col_invoicedateupdater.cpp \
    col_threadedinvoicedatechanger.cpp \
    col_transactions.cpp \
    col_calendar.cpp

HEADERS += collectionplugin.h \
    collectionmainwindow.h \
    col_customerlist.h \
    col_invoicelist.h \
    col_localinvoices.h \
    col_invoicefetcher.h \
    col_threadedinvoicefetcher.h \
    col_ageing.h \
    col_invoicedateupdater.h \
    col_threadedinvoicedatechanger.h \
    col_transactions.h \
    col_calendar.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    collectionmainwindow.ui \
    col_customerlist.ui \
    col_invoicelist.ui \
    col_localinvoices.ui \
    col_invoicefetcher.ui \
    col_ageing.ui \
    col_invoicedateupdater.ui \
    col_transactions.ui \
    col_calendar.ui
