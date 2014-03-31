#-------------------------------------------------
#
# Project created by QtCreator 2014-03-31T11:22:22
#
#-------------------------------------------------

QT       += core sql network
DESTDIR = ../../build/

QT       -= gui
LIBS += -L../../build -ldatapublics
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
    smtpclient/smtpclient.cpp

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
    smtpclient/SmtpMime
