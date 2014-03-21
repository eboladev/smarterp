#include "smartocprinter.h"
#include "ui_smartocprinter.h"

#include "specialprintdialog.h"

SmartOcPrinter::SmartOcPrinter(QDomDocument doc, QSqlDatabase database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmartOcPrinter),
    _doc(doc), db(database)
{
    ui->setupUi(this);

    printer = new QPrinter(QPrinter::HighResolution);
    QSizeF size(8.5, 5.5);
    printer->setPaperSize(size, QPrinter::Inch);

    connect (ui->cmdZoomIn, SIGNAL(clicked()),
             SLOT(zoomIn()));
    connect (ui->cmdZoomOut, SIGNAL(clicked()),
             SLOT(zoomOut()));

    connect (ui->cmdPDF, SIGNAL(clicked()),
             SLOT(makePDF()));

    connect (ui->cmdPrint, SIGNAL(clicked()),
             SLOT(print()));

    connect (ui->previewWidget, SIGNAL(paintRequested(QPrinter*)),
             SLOT(previewRequested(QPrinter*)));

}

SmartOcPrinter::~SmartOcPrinter()
{
    delete ui;
}

void SmartOcPrinter::zoomIn()
{

}

void SmartOcPrinter::zoomOut()
{

}

void SmartOcPrinter::print()
{
    QPrinter *prnt = new QPrinter(QPrinter::HighResolution);
    SpecialPrintDialog dg(prnt, 0);
    if (dg.exec() == QDialog::Accepted) {
        previewRequested(prnt);
    }
}

void SmartOcPrinter::makePDF()
{

}

void SmartOcPrinter::previewRequested(QPrinter *prnt)
{
    QSizeF size(8.5, 5.5);
    prnt->setPaperSize(size, QPrinter::Inch);
    ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(_doc);
    ORODocument *oDoc = pre.generate();
    if (oDoc) {
        ORPrintRender render;
        render.setPrinter(prnt);

        ReportPageOptions opt;
        opt.setCustomHeight(5.5);
        opt.setCustomWidth(8.5);

        oDoc->setPageOptions(opt);

        render.renderOC(oDoc);
        render.setupOcPrinter(oDoc, prnt);
        prnt->setFullPage(true);
        QSizeF size(8.5, 5.5);
        prnt->setPaperSize(size, QPrinter::Inch);
    }
}
