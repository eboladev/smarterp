#include "chequerenderer.h"
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
#include "smartpreviewdialog.h"
ChequeRenderer::ChequeRenderer(QWidget *parent, QString session_id, QSqlDatabase database, bool makePdf) :
    QObject(parent)
{
    setIsPdf(makePdf);
    QString reportName = "Cheque";
    m_ocNo = session_id;
    db = database;
    printer = new QPrinter(QPrinter::ScreenResolution);
    printer->setCreator("Smart Software Ltd");

    QString xml = makeXml(db, "DTB");
    _xml = xml;
    QDomDocument doc;
    QString errMsg;
    int errLine, errColm;
    if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
    {
        QMessageBox::critical(0, tr("Error Loading Report 1"),
                              tr("There was an error opening the report %1."
                                 "\n\n%2 on line %3 column %4.")
                              .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        QMessageBox::critical(0, tr("Not a valid file 2"),
                              tr("The file %1 does not appear to ba a valid file"
                                 "\n\nThe root node is not 'report'.").arg(reportName));
        return;
    }
    _doc = doc;
    ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(_doc);
    ORODocument *oDoc = pre.generate();

    QSizeF size(7, 4);
    printer->setPaperSize(size, QPrinter::Inch);

    if (m_isPdf) {
        printer->setOutputFormat(QPrinter::PdfFormat);
        QString fileName = QFileDialog::getSaveFileName(0
                                                        , "Pdf File Name"
                                                        , ""
                                                        , "Pdf Document (*.pdf)");
        if (fileName.length() > 0) {
            printer->setOutputFileName(fileName);
        } else {
            return;
        }
    } else {
        SmartPreviewDialog pv( oDoc, printer, 0);
        pv.setWindowTitle("Printing Cheque(s)");
        int res = pv.exec();
        if (res == 1) {
            QPrintDialog dg(printer, 0);
            if (dg.exec() == QDialog::Accepted) {
                ORPreRender pre;
                pre.setDatabase(db);
                pre.setDom(_doc);
                ORODocument *oDoc = pre.generate();
                if (oDoc) {
                    ORPrintRender render;
                    render.setPrinter(printer);
                    render.render(oDoc);
                    render.setupPrinter(oDoc, printer);
                    QSizeF size(7, 4);
                    printer->setPaperSize(size, QPrinter::Inch);
                } else {
                    DataPublics::showWarning("Printer Error");
                }
            } //Print Dialog cancelled

        } //Preview Dialog Cancelled
    }
}


bool ChequeRenderer::isPdf() const
{
    return m_isPdf;
}

void ChequeRenderer::setIsPdf(bool isPdf)
{
    m_isPdf = isPdf;
}

void ChequeRenderer::renderOnPrinter(QPrinter *prnt, QSqlDatabase m_db, QString profile)
{
    QString xml = makeXml(m_db, profile);
    QDomDocument doc;
    QString errMsg;
    int errLine, errColm;
    if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
    {
        QMessageBox::critical(0, tr("Error Loading Report 1"),
                              tr("There was an error opening the report %1."
                                 "\n\n%2 on line %3 column %4.")
                              .arg("Cheque").arg(errMsg).arg(errLine).arg(errColm) );
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        QMessageBox::critical(0, tr("Not a valid file 2"),
                              tr("The file %1 does not appear to ba a valid file"
                                 "\n\nThe root node is not 'report'.").arg("Cheque"));
        return;
    }
    ORPreRender pre;
    pre.setDatabase(m_db);
    pre.setDom(doc);
    ORODocument *oDoc = pre.generate();

    ORPrintRender render;
    render.setPrinter(prnt);
    render.render(oDoc);
    render.setupPrinter(oDoc, prnt);
}

QString ChequeRenderer::makeXml(QSqlDatabase m_db, QString profile)
{
    double page_height = 4;
    double page_width = 7;

    QSqlQuery pg_set_qu = m_db.exec("SELECT * FROM page_settings");
    if (pg_set_qu.first()) {
        page_height = pg_set_qu.record().value("PageHeight").toDouble();
        page_width = pg_set_qu.record().value("PageWidth").toDouble();
    }


    QString xml = "<!DOCTYPE openRPTDef> "
            " <report> "
            " <title>Cheque</title> "
            "  <name>Cheque</name> "
            " <description>Cheque</description> "
            " <grid> "
            "  <snap/> "
            " <show/> "
            " <x>0.05</x> "
            "  <y>0.05</y> "
            "  </grid> "
            "  <size> "
            "  <width>" + QString::number(page_width * 100) +"</width> "
            "  <height>" + QString::number(page_height * 100) +"</height> "
            " </size> "
            "  <portrait/> "
            "  <topmargin>10</topmargin> "
            " <bottommargin>10</bottommargin> "
            " <rightmargin>10</rightmargin> "
            " <leftmargin>0</leftmargin> "
            " <querysource> "
            "  <name>Master</name> "
            " <sql>SELECT * FROM cheques</sql> "
            " </querysource> "
            "   <section> "
            "    <name>unnamed</name> "
            "   <detail> "
            "  <key> "
            "<query>Master</query> "
            "</key>"
            "<height>370</height>";

    QSqlQuery f_qu = m_db.exec("SELECT * FROM fields WHERE Profile = '" + profile + "'");

    while (f_qu.next()) {
        QString fieldXml = "";
        fieldXml += "<field>"
                "<rect>"
                "<x>" + f_qu.record().value("X").toString() + "</x>"
                "<y>" + f_qu.record().value("Y").toString() + "</y>"
                "<width>" + f_qu.record().value("Width").toString() + "</width>"
                "<height>" + f_qu.record().value("Height").toString() + "</height>"
                "</rect>"
                "<font>"
                "<face>Verdana</face>"
                "<size>" + f_qu.record().value("FontSize").toString() + "</size>"
                "<weight>normal</weight>"
                "</font>";
        if  (f_qu.record().value("WordWrap").toString() == "Yes")
        {
            fieldXml += "<wordwrap/>";
        }
        fieldXml +=          "<left/>"
                "<top/>"
                "<data>"
                "<query>Master</query>"
                "<column>" + f_qu.record().value("Column").toString() + "</column>"
                "</data>"
                "</field>";

        xml += fieldXml;
    }

    xml += "</detail>"
            "</section>"
            "</report>";

    //qDebug() << xml;
    return xml;
}

