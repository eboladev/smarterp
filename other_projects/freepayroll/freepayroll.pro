#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T10:58:22
#
#-------------------------------------------------

QT       += core gui sql xml
DESTDIR = ../../build
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = FreePayroll
TEMPLATE = app


SOURCES += main.cpp\
        freepayrollmw.cpp \
    payrollapi.cpp \
    companyinformationdialog.cpp \
    brancheditor.cpp \
    departmenteditor.cpp \
    jobgroupeditor.cpp \
    cooperatives.cpp \
    pensions.cpp \
    employeeeditor.cpp \
    startnewemployeedialog.cpp \
    calendardateselector.cpp \
    aboutdialog.cpp

HEADERS  += freepayrollmw.h \
    payrollapi.h \
    companyinformationdialog.h \
    brancheditor.h \
    departmenteditor.h \
    jobgroupeditor.h \
    cooperatives.h \
    pensions.h \
    employeeeditor.h \
    startnewemployeedialog.h \
    calendardateselector.h \
    aboutdialog.h

FORMS    += freepayrollmw.ui \
    companyinformationdialog.ui \
    brancheditor.ui \
    departmenteditor.ui \
    jobgroupeditor.ui \
    cooperatives.ui \
    pensions.ui \
    employeeeditor.ui \
    startnewemployeedialog.ui \
    calendardateselector.ui \
    aboutdialog.ui

RESOURCES += \
    res.qrc

win32:RC_FILE=app.rc
