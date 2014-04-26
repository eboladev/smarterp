#-------------------------------------------------
#
# Project created by QtCreator 2012-05-15T14:02:04
#
#-------------------------------------------------
TARGET = datapublics
TEMPLATE = lib
DEFINES += MAKELIB
#CONFIG += qt warn_on staticlib shared
DESTDIR += ../../build
QT += gui sql xml network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
INCLUDEPATH +=  ../common ../../common ../OpenRPT/renderer
LIBS += -L../../build -lrenderer -lcommon

SOURCES += datapublics.cpp \
    reportpreview.cpp \
    mailassistant.cpp \
    smtpclient/smtpclient.cpp \
    smtpclient/quotedprintable.cpp \
    smtpclient/mimetext.cpp \
    smtpclient/mimepart.cpp \
    smtpclient/mimemultipart.cpp \
    smtpclient/mimemessage.cpp \
    smtpclient/mimeinlinefile.cpp \
    smtpclient/mimehtml.cpp \
    smtpclient/mimefile.cpp \
    smtpclient/mimecontentformatter.cpp \
    smtpclient/mimeattachment.cpp \
    smtpclient/emailaddress.cpp \
    htmlgenerator.cpp \
    exportexcelobject.cpp \
    publicprinter.cpp \
    qtprinter.cpp \
    htmltoqtprinter.cpp \
    smartpreviewwidget.cpp \
    smartpreviewdialog.cpp

HEADERS += datapublics.h\
        DataPublics_global.h \
    interfaces.h \
    reportpreview.h \
    mailassistant.h \
    smtpclient/SmtpMime \
    smtpclient/smtpclient.h \
    smtpclient/quotedprintable.h \
    smtpclient/mimetext.h \
    smtpclient/mimepart.h \
    smtpclient/mimemultipart.h \
    smtpclient/mimemessage.h \
    smtpclient/mimeinlinefile.h \
    smtpclient/mimehtml.h \
    smtpclient/mimefile.h \
    smtpclient/mimecontentformatter.h \
    smtpclient/mimeattachment.h \
    smtpclient/emailaddress.h \
    htmlgenerator.h \
    exportexcelobject.h \
    publicprinter.h \
    qtprinter.h \
    htmltoqtprinter.h \
    smartpreviewwidget.h \
    smartpreviewdialog.h


FORMS += \
    reportpreview.ui \
    smartpreviewdialog.ui

OTHER_FILES +=
