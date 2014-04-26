#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T14:45:42
#
#-------------------------------------------------

QT +=  core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = auto_intro
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += . ../../universal/common ../../universal/OpenRPT/common ../../universal/OpenRPT/renderer
INCLUDEPATH +=  ../../universal/custom_widgets
INCLUDEPATH +=  ../../universal/qcustomplot
LIBS += -L../../build  -lxlslib
LIBS += -L../../build -lcustom_widgets -lmanhattanstyle -lrenderer  -lcommon -lqcustomplot
LIBS += -L../../build -ldatapublics -lcustommodels

SOURCES += intromainwindow.cpp \
    autointroplugin.cpp

HEADERS  += intromainwindow.h \
    autointroplugin.h

FORMS    += intromainwindow.ui

RESOURCES += \
    res.qrc
