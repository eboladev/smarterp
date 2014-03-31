#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T10:36:05
#
#-------------------------------------------------

QT       += core gui sql xml
DESTDIR = ../../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += . ../../universal/common ../../universal/openrpt/common ../../universal/openrpt/renderer

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

include(../../universal/qtxlsx/src/xlsx/qtxlsx.pri)


TARGET = FreeSacco
TEMPLATE = app


SOURCES += main.cpp\
        saccomainwindow.cpp \
    src/membermanager.cpp \
    src/companymanager.cpp \
    src/membereditordialog.cpp \
    src/startnewmemberdialog.cpp

HEADERS  += saccomainwindow.h \
    src/membermanager.h \
    src/companymanager.h \
    src/membereditordialog.h \
    src/startnewmemberdialog.h

FORMS    += saccomainwindow.ui \
    src/membermanager.ui \
    src/companymanager.ui \
    src/membereditordialog.ui \
    src/startnewmemberdialog.ui

RC_FILE += \
    app.rc

OTHER_FILES += \
    app.manifest

RESOURCES += \
    sacco_rc.qrc
