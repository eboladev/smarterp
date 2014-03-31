QT       += core gui  sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = school_students
TEMPLATE = lib
DESTDIR = ../../build/plugins
INCLUDEPATH += ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels ../../universal/OpenRPT/renderer ../../universal/common ../../universal/common
LIBS += -L../../lib -ldatapublics
LIBS += -L../../lib -lmanhattanstyle -lcustommodels -lrenderer -lcommon


HEADERS += \
    studentsmainwindow.h \
    school_studentsplugin.h \
    newstudent.h \
    newstudentwizard.h

SOURCES += \
    studentsmainwindow.cpp \
    school_studentsplugin.cpp \
    newstudent.cpp \
    newstudentwizard.cpp

FORMS += \
    studentsmainwindow.ui \
    newstudent.ui \
    newstudentwizard.ui
