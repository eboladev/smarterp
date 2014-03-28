#include "qtprinter.h"
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include "renderobjects.h"
#include "openreports.h"
#include "orprerender.h"
#include "orprintrender.h"
#include "parameterproperties.h"
#include "data.h"
#include "parsexmlutils.h"
#include "paramlistedit.h"
#include "previewdialog.h"
#include "builtinSqlFunctions.h"
#include <QMessageBox>
#include <QFileDialog>
#include "datapublics.h"
#include <QPrintDialog>
QtPrinter::QtPrinter(QWidget *parent, QSqlDatabase database, QString where, QString report, bool pdf) :
    QObject(parent)
{
    db = database;
    param = where;
    reportName = report;
    makePdf = pdf;
    openPdf = false;
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setCreator("Megvel Cartons Ltd");

    QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '"  + reportName + "'");
    if (!qu.lastError().isValid()) {
        qu.last();
        QString xml = qu.record().value("report_source").toString();
        xml.replace("param_where", where);
        _xml = xml;
        QDomDocument doc;
        QString errMsg;
        int errLine, errColm;
        if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
        {
            QMessageBox::critical(0, tr("Error Loading Report"),
                                  tr("There was an error opening the report %1."
                                     "\n\n%2 on line %3 column %4.")
                                  .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
            return;
        }

        QDomElement root = doc.documentElement();
        if (root.tagName() != "report") {
            QMessageBox::critical(0, tr("Not a valid file"),
                                  tr("The file %1 does not appear to ba a valid file"
                                     "\n\nThe root node is not 'report'.").arg(reportName));
            return;
        }
        _doc = doc;
        QtPrinter(parent, database, xml, makePdf);
    } else {
        DataPublics::showWarning("Fatal error: Could not generate report.\n\n" + qu.lastError().text());
    }
}

QtPrinter::QtPrinter(QWidget *parent, QSqlDatabase database, QString where, QString report, QString autoPdf)
{
    QString p = autoPdf;
    p = "Yes";
    openPdf = true;
    db = database;
    param = where;
    reportName = report;
    makePdf = true;
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setCreator("Smart Software Ltd");

    QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '"  + reportName + "'");
    if (!qu.lastError().isValid()) {
        qu.last();
        QString xml = qu.record().value("report_source").toString();
        xml.replace("param_where", where);
        _xml = xml;
        QDomDocument doc;
        QString errMsg;
        int errLine, errColm;
        if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
        {
            QMessageBox::critical(0, tr("Error Loading Report"),
                                  tr("There was an error opening the report %1."
                                     "\n\n%2 on line %3 column %4.")
                                  .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
            return;
        }

        QDomElement root = doc.documentElement();
        if (root.tagName() != "report") {
            QMessageBox::critical(0, tr("Not a valid file"),
                                  tr("The file %1 does not appear to ba a valid file"
                                     "\n\nThe root node is not 'report'.").arg(reportName));
            return;
        }
        _doc = doc;
        QtPrinter(parent, database, xml, makePdf);
    } else {
        DataPublics::showWarning("Fatal error: Could not generate report.\n\n" + qu.lastError().text());
    }
}

QtPrinter::QtPrinter(QWidget *parent, QSqlDatabase database, QString reportXml, bool pdf)
{
    Q_UNUSED(parent);
    openPdf = false;
    db = database;
    makePdf = pdf;
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setCreator("Megvel Cartons Ltd");
    printer->setPageSize(QPrinter::Letter);
    _xml = reportXml;
    QDomDocument doc;
    QString errMsg;
    int errLine, errColm;
    if (!doc.setContent(reportXml, &errMsg, &errLine, &errColm))
    {
        QMessageBox::critical(0, tr("Error Loading Report"),
                              tr("There was an error opening the report %1."
                                 "\n\n%2 on line %3 column %4.")
                              .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        QMessageBox::critical(0, tr("Not a valid file"),
                              tr("The file %1 does not appear to ba a valid file"
                                 "\n\nThe root node is not 'report'.").arg(reportName));
        return;
    }
    _doc = doc;

    if (!makePdf) {

        ORPreRender pre;
        pre.setDatabase(db);
        pre.setDom(_doc);
        ORODocument *oDoc = pre.generate();
        PreviewDialog pv( oDoc, printer, 0);
        if (pv.exec() == QDialog::Accepted) {
            QPrintDialog *dg = new QPrintDialog(printer, 0);
            connect (dg, SIGNAL(accepted(QPrinter*)), SLOT(printRequested(QPrinter*)));


            if (dg->exec() == 1) {
            }
        }
    } else {
        printRequested(printer);
    }


}


void QtPrinter::printRequested(QPrinter *printer)
{
    ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(_doc);
    QString fileName;
    ORODocument *oDoc = pre.generate();
    if (oDoc) {
        if (makePdf) {
            fileName = QFileDialog::getSaveFileName(0, "Save PDF"
                                                    , QDir::homePath()  + QDir::separator() + "MarineDeclaration.pdf"
                                                    , tr("PDF Files (*.pdf)"));
            if (!fileName.endsWith(".pdf"))
                fileName.append(".pdf");

            if (fileName.length() > 0) {
                printer->setOutputFormat(QPrinter::PdfFormat);
                printer->setOutputFileName(fileName);
            } else {
                DataPublics::showWarning("Error:\n\nFile name not specified.");
                return;
            }
        }
        ORPrintRender render;
        render.setPrinter(printer);
        render.render(oDoc);
        render.setupPrinter(oDoc, printer);
        if (makePdf) {
            DataPublics::showInformation("PDF successfuly generated.");
            QFile fl(fileName);
            if (fl.exists()) {
                QDesktopServices::openUrl(QUrl(fileName));
            }
        }
    }
}
