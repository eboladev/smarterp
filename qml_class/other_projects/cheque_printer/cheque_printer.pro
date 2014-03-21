#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T09:39:40
#
#-------------------------------------------------

QT       += core gui sql xml
DESTDIR = ../../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TARGET = cheque_printer
TEMPLATE = app

INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += . ../../universal/common ../../universal/openrpt/common ../../universal/openrpt/renderer

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

include(../../universal/qtxlsx/src/xlsx/qtxlsx.pri)

SOURCES += main.cpp\
        chequeprinter.cpp \
    threadedexcelimporter.cpp \
    supplierimportprogressdialog.cpp \
    chequerenderer.cpp \
    printoutsettingsdialog.cpp \
    aboutdialog.cpp

HEADERS  += chequeprinter.h \
    threadedexcelimporter.h \
    supplierimportprogressdialog.h \
    chequerenderer.h \
    printoutsettingsdialog.h \
    aboutdialog.h

FORMS    += chequeprinter.ui \
    supplierimportprogressdialog.ui \
    printoutsettingsdialog.ui \
    aboutdialog.ui

RC_FILE += \
    app.rc

OTHER_FILES += \
    app.manifest

RESOURCES += \
    cp_res.qrc
