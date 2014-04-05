#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T11:22:22
#
#-------------------------------------------------

QT       += core sql network xml
DESTDIR = ../../build/
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
QT       -= gui

INCLUDEPATH +=  . ../../universal/DataPublics
INCLUDEPATH += ../../universal/common ../../universal/OpenRPT/renderer ../../universal/OpenRPT/common ../../universal/common/tmp


LIBS += -L../../build -ldatapublics
LIBS += -L../../build -lrenderer  -lcommon

TARGET = erp_mailer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mailerparent.cpp \
    smtpclient/emailaddress.cpp \
    smtpclient/mimeattachment.cpp \
    smtpclient/mimecontentformatter.cpp \
    smtpclient/mimefile.cpp \
    smtpclient/mimehtml.cpp \
    smtpclient/mimeinlinefile.cpp \
    smtpclient/mimemessage.cpp \
    smtpclient/mimemultipart.cpp \
    smtpclient/mimepart.cpp \
    smtpclient/mimetext.cpp \
    smtpclient/quotedprintable.cpp \
    smtpclient/smtpclient.cpp \
    generatehtmllpo.cpp

HEADERS += \
    mailerparent.h \
    smtpclient/emailaddress.h \
    smtpclient/mimeattachment.h \
    smtpclient/mimecontentformatter.h \
    smtpclient/mimefile.h \
    smtpclient/mimehtml.h \
    smtpclient/mimeinlinefile.h \
    smtpclient/mimemessage.h \
    smtpclient/mimemultipart.h \
    smtpclient/mimepart.h \
    smtpclient/mimetext.h \
    smtpclient/quotedprintable.h \
    smtpclient/smtpclient.h \
    smtpclient/SmtpMime \
    generatehtmllpo.h
