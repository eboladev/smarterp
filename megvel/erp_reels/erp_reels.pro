QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_reels
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon
DEFINES += ERP_REELS_LIBRARY


SOURCES += \
    reelsplugin.cpp \
    reelsmainwindow.cpp \
    newreel.cpp \
    editreel.cpp \
    ean13.cpp \
    BarCodeWidget.cpp

HEADERS += \
    reelsmainwindow.h \
    reelsplugin.h \
    newreel.h \
    editreel.h \
    ean13.h \
    BarCodeWidget.h

FORMS += \
    reelsmainwindow.ui \
    newreel.ui \
    editreel.ui
