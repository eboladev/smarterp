#-------------------------------------------------
#
# Project created by QtCreator 2012-05-17T10:10:27
#
#-------------------------------------------------

QT +=  core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport
TEMPLATE = lib
CONFIG += plugin
TARGET = erp_customers
DESTDIR = ../../build/plugins
INCLUDEPATH +=  ../../universal/ManhattanStyle ../../universal/DataPublics ../../universal/CustomModels
INCLUDEPATH += . ../../universal/common ../../universal/OpenRPT/common ../../universal/OpenRPT/renderer
INCLUDEPATH +=  ../../universal/custom_widgets
INCLUDEPATH +=  ../../universal/qcustomplot
LIBS += -L../../build  -lxlslib
LIBS += -L../../build -lcustom_widgets -lmanhattanstyle -lrenderer  -lcommon -lqcustomplot
LIBS += -L../../build -ldatapublics -lcustommodels
win32:LIBS += -lwinspool
DEFINES += ERP_CUSTOMERS_LIBRARY

SOURCES += customersplugin.cpp \
    customers.cpp \
    customereditor.cpp \
    customermainwindow.cpp \
    ocs.cpp \
    editproduct.cpp \
    createproforma.cpp \
    productsapproval.cpp \
    generatejobtickets.cpp \
    productcalculations.cpp \
    purchaseorders.cpp \
    newlpo.cpp \
    ocregister.cpp \
    startnewproduct.cpp \
    lpooclinker.cpp \
    calculations/product.cpp \
    calculations/jobticket.cpp \
    proformalist.cpp \
    generateproformainvoice.cpp \
    jobticketprinter.cpp \
    productsmodel.cpp \
    customersmodel.cpp \
    smartocprinter.cpp \
    specialprintdialog.cpp

HEADERS += customersplugin.h\
        erp_customers_global.h \
    customers.h \
    customereditor.h \
    customermainwindow.h \
    ocs.h \
    editproduct.h \
    createproforma.h \
    productsapproval.h \
    generatejobtickets.h \
    productcalculations.h \
    purchaseorders.h \
    newlpo.h \
    ocregister.h \
    startnewproduct.h \
    lpooclinker.h \
    calculations/product.h \
    calculations/jobticket.h \
    proformalist.h \
    generateproformainvoice.h \
    jobticketprinter.h \
    productsmodel.h \
    customersmodel.h \
    smartocprinter.h \
    specialprintdialog.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0DDEA86
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = erp_customers.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    customers.ui \
    customereditor.ui \
    customermainwindow.ui \
    ocs.ui \
    editproduct.ui \
    createproforma.ui \
    productsapproval.ui \
    generatejobtickets.ui \
    purchaseorders.ui \
    newlpo.ui \
    ocregister.ui \
    startnewproduct.ui \
    lpooclinker.ui \
    proformalist.ui \
    generateproformainvoice.ui \
    smartocprinter.ui \
    specialprintdialog.ui

OTHER_FILES += \
    xxx.css

RESOURCES += \
    res.qrc
