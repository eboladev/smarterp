#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T12:14:41
#
#-------------------------------------------------

QT += core gui xml sql
TEMPLATE = lib
TARGET = smartpay
#DEPENDPATH += .
INCLUDEPATH += . ./src src ../ManhattanStyle ../ManhattanStyle/Utils ../common ../OpenRPT/renderer ../OpenRPT/common ../common/tmp ../../common/tmp ../DataPublics ../CustomModels
CONFIG += plugin
DESTDIR = ../../build/plugins

LIBS += -L../../lib -lmanhattanstyle -lcustommodels -lrenderer  -lcommon
LIBS += -L../../lib -ldatapublics

SOURCES +=\
        src/mainwindow.cpp \
    src/employees.cpp \
    src/lists.cpp \
    src/selectemployee.cpp \
    src/departments.cpp \
    src/jobtitles.cpp \
    src/holidays.cpp \
    src/payrollmonths.cpp \
    src/publics.cpp \
    src/issueadvance.cpp \
    src/leaves.cpp \
    src/shifts.cpp \
    src/saccos.cpp \
    src/payroll.cpp \
    src/reportviewer.cpp \
    src/attendance.cpp \
    src/uploadattendance.cpp \
    src/timetable.cpp \
    src/createtimetable.cpp \
    src/hourcalculator.cpp \
    src/recalculateattendance.cpp \
    src/admin.cpp \
    src/threadedatt.cpp \
    src/userlogin.cpp \
    src/myaccount.cpp \
    src/threadedattendancecalc.cpp \
    src/threadedcreatetimetable.cpp \
    src/makesaccopayment.cpp \
    src/autoclockin.cpp \
    src/smartpayplugin.cpp \
    src/manualclockin.cpp \
    src/threadedmanualclockinout.cpp \
    src/createregister.cpp \
    src/threadedregister.cpp \
    src/payslips.cpp

HEADERS  += src/mainwindow.h \
    src/employees.h \
    src/lists.h \
    src/selectemployee.h \
    src/departments.h \
    src/jobtitles.h \
    src/holidays.h \
    src/payrollmonths.h \
    src/publics.h \
    src/issueadvance.h \
    src/leaves.h \
    src/shifts.h \
    src/saccos.h \
    src/payroll.h \
    src/reportviewer.h \
    src/attendance.h \
    src/uploadattendance.h \
    src/timetable.h \
    src/createtimetable.h \
    src/hourcalculator.h \
    src/recalculateattendance.h \
    src/admin.h \
    src/threadedatt.h \
    src/userlogin.h \
    src/myaccount.h \
    src/threadedattendancecalc.h \
    src/threadedcreatetimetable.h \
    src/makesaccopayment.h \
    src/autoclockin.h \
    src/smartpay_global.h \
    src/smartpayplugin.h \
    src/manualclockin.h \
    src/threadedmanualclockinout.h \
    src/createregister.h \
    src/threadedregister.h \
    src/payslips.h

FORMS    += src/mainwindow.ui \
    src/employees.ui \
    src/lists.ui \
    src/selectemployee.ui \
    src/departments.ui \
    src/jobtitles.ui \
    src/holidays.ui \
    src/payrollmonths.ui \
    src/issueadvance.ui \
    src/leaves.ui \
    src/shifts.ui \
    src/saccos.ui \
    src/payroll.ui \
    src/reportviewer.ui \
    src/attendance.ui \
    src/uploadattendance.ui \
    src/timetable.ui \
    src/createtimetable.ui \
    src/recalculateattendance.ui \
    src/admin.ui \
    src/userlogin.ui \
    src/myaccount.ui \
    src/makesaccopayment.ui \
    src/autoclockin.ui \
    src/manualclockin.ui \
    src/createregister.ui \
    src/payslips.ui

RESOURCES += \
    src/rc.qrc \
    src/res.qrc

RC_FILE = SmartPay.rc
