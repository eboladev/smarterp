#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T10:13:34
#
#-------------------------------------------------

QT       += core gui sql xml network

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

QT       += core gui sql xml network
DESTDIR = ../../build
win32:TARGET = ScheduledReports(MCL)
unix:TARGET = mcl_scheduled_reports

INCLUDEPATH += . ./src src ../ManhattanStyle ../ManhattanStyle/Utils ../common ../OpenRPT/renderer ../OpenRPT/common ../common/tmp ../../common/tmp ../DataPublics ../CustomModels
LIBS += -L../../build -lcustommodels -lxlslib
LIBS += -L../../build -ldatapublics -lmanhattanstyle -lrenderer  -lcommon


SOURCES += main.cpp\
        scheduledreportsmainwindow.cpp \
    reporteditor.cpp

HEADERS  += scheduledreportsmainwindow.h \
    reporteditor.h

FORMS    += scheduledreportsmainwindow.ui \
    reporteditor.ui

RC_FILE += \
    app.rc

RESOURCES += \
    ../../home/src/res.qrc \
    ../reportmaster/src/res.qrc
