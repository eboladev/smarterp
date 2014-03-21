#-------------------------------------------------
#
# Project created by QtCreator 2013-02-07T10:12:25
#
#-------------------------------------------------

QT       += core gui sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
#CONFIG += qxt
#QXT += core gui

TEMPLATE = lib
TARGET = xpert-debtcollection
CONFIG +=   plugin
DESTDIR     = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels


#INCLUDEPATH += . ./src src ../ManhattanStyle ../ManhattanStyle/Utils ../common ../OpenRPT/renderer ../OpenRPT/common ../common/tmp ../../common/tmp ../DataPublics ../CustomModels

LIBS += -L../../build -lcustommodels -lxlslib -ldatapublics
LIBS += -L../../build -lmanhattanstyle -lrenderer  -lcommon

DEFINES += ERP_DEBTCOLLECTION_LIBRARY

INCLUDEPATH += . quickcalendarview

#SOURCES += main.cpp\
 SOURCES +=   dcmainwindow.cpp \
    customersearchwidget.cpp \
    newactionwizard.cpp \
    extendedcalendarwidget.cpp \
    newfiledialog.cpp \
    publics.cpp \
    quickcalendarview/weekitem.cpp \
    quickcalendarview/weekdayheaderitem.cpp \
    quickcalendarview/selectorwidget.cpp \
    quickcalendarview/scrollbar.cpp \
    quickcalendarview/scrollareaitem.cpp \
    quickcalendarview/quickcalendarwindow.cpp \
    quickcalendarview/quickcalendarstyle.cpp \
    quickcalendarview/dayitem.cpp \
    quickcalendarview/daycontentitem.cpp \
    quickcalendarview/clockbar.cpp \
    quickcalendarview/calendaritem.cpp \
    quickcalendarview/calendar.cpp \
    quickcalendarview/appointmentitem.cpp \
    quickcalendarview/appointment.cpp \
    quickcalendarview/appointmentdetailsform.cpp \
    quickcalendarview/quickcalendarview.cpp \
    quickcalendarview/calendartablemodel.cpp \
    actiontypes.cpp \
    mymodels.cpp \
    transactionview.cpp \
    newphonecall.cpp \
    debtcollectionplugin.cpp \
    extendednewaction.cpp \
    chequesmw.cpp \
    chequeeditor.cpp \
    chequedeposit.cpp
HEADERS  += dcmainwindow.h \
    customersearchwidget.h \
    newactionwizard.h \
    extendedcalendarwidget.h \
    newfiledialog.h \
    publics.h \
    quickcalendarview/weekitem.h \
    quickcalendarview/weekdayheaderitem.h \
    quickcalendarview/ui_quickcalendarwindow.h \
    quickcalendarview/selectorwidget.h \
    quickcalendarview/scrollbar.h \
    quickcalendarview/scrollareaitem.h \
    quickcalendarview/quickcalendarwindow.h \
    quickcalendarview/quickcalendarstyle.h \
    quickcalendarview/dayitem.h \
    quickcalendarview/daycontentitem.h \
    quickcalendarview/clockbar.h \
    quickcalendarview/calendaritem.h \
    quickcalendarview/calendar.h \
    quickcalendarview/appointmentitem.h \
    quickcalendarview/appointmentdetailsform.h \
    quickcalendarview/appointment.h \
    quickcalendarview/quickcalendarview.h \
    quickcalendarview/weekheaderitem.h \
    quickcalendarview/calendartablemodel.h \
    actiontypes.h \
    mymodels.h \
    transactionview.h \
    newphonecall.h \
    debtcollectionplugin.h \
    extendednewaction.h \
    chequesmw.h \
    chequeeditor.h \
    chequedeposit.h

FORMS    += dcmainwindow.ui \
    customersearchwidget.ui \
    newactionwizard.ui \
    extendedcalendarwidget.ui \
    newfiledialog.ui \
    quickcalendarview/quickcalendarwindow.ui \
    quickcalendarview/calendardetailsform.ui \
    quickcalendarview/appointmentdetailsform.ui \
    actiontypes.ui \
    transactionview.ui \
    newphonecall.ui \
    extendednewaction.ui \
    chequesmw.ui \
    chequeeditor.ui \
    chequedeposit.ui

RESOURCES += \
    res.qrc

#LIBS += -L ..\libqxt-libqxt-5b312c4b7d0b\lib -lqxtcore -lqxtwidgets
