QT += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
TARGET = erp_company
DESTDIR = ../../build/plugins
CONFIG += plugin
#INCLUDEPATH += . ../MegvelERP/src
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/OpenRPT/renderer ../../universal/common ../../universal/common


LIBS += -L../../build  -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer -lcommon


HEADERS += \
    companyplugin.h \
    users.h \
    usereditor.h \
    company.h \
    rolesmanager.h \
    salesreps.h \
    salesrepeditor.h \
    datamanager.h

SOURCES += \
    company.cpp \
    companyplugin.cpp \
    users.cpp \
    usereditor.cpp \
    rolesmanager.cpp \
    salesreps.cpp \
    salesrepeditor.cpp \
    datamanager.cpp

FORMS += \
    company.ui \
    users.ui \
    usereditor.ui \
    rolesmanager.ui \
    salesreps.ui \
    salesrepeditor.ui \
    datamanager.ui
