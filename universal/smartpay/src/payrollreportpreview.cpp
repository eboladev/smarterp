#include "payrollreportpreview.h"
#include "ui_payrollreportpreview.h"

PayrollReportPreview::PayrollReportPreview(QWidget *parent, QPrinter *p) :
    QWidget(parent),
    ui(new Ui::PayrollReportPreview)
{
    ui->setupUi(this);
    m_printer = p;
    previewWidget = new QPrintPreviewWidget(m_printer);
    ui->vLay->addWidget(previewWidget);


    connect (previewWidget, SIGNAL(paintRequested(QPrinter*))
             ,this, SLOT(showPreview()));

    connect (previewWidget, SIGNAL(previewChanged()), SLOT(changed()));
}

PayrollReportPreview::~PayrollReportPreview()
{
    delete ui;
}
QPrinter *PayrollReportPreview::printer() const
{
    return m_printer;
}

void PayrollReportPreview::setPrinter(QPrinter *printer)
{
    m_printer = printer;
}

void PayrollReportPreview::setVars(ORPreRender pr, ORODocument *doc)
{
    pre = pr;
    oDoc = doc;
}

void PayrollReportPreview::showPreview()
{
    delete(previewWidget);

    previewWidget = new QPrintPreviewWidget(m_printer);
    connect (previewWidget, SIGNAL(paintRequested(QPrinter *)), this,
             SLOT(drawReport(QPrinter*)));

    ui->vLay->addWidget(previewWidget);
}


void PayrollReportPreview::on_cmdZoomIn_clicked()
{
    previewWidget->zoomIn();
}

void PayrollReportPreview::on_cmdZoomOut_clicked()
{
    previewWidget->zoomOut();
}

#include <QPrintDialog>
void PayrollReportPreview::on_cmdPrint_clicked()
{
    QPrintDialog *p = new QPrintDialog(m_printer, this);

    connect (p, SIGNAL(accepted(QPrinter*)), SLOT(printRequesed(QPrinter*)));

    p->exec();
}

void PayrollReportPreview::printRequesed(QPrinter *pr)
{
    if (oDoc) {
        ORPrintRender render;
        render.setPrinter(pr);
        render.render(oDoc);
        render.setupPrinter(oDoc, pr);
    }
}

void PayrollReportPreview::drawReport(QPrinter *p)
{
    p->setCreator("Smart Pay");

    QString xml = m_xml;
    if (xml.contains("<landscape/>"))
    {
        p->setOrientation(QPrinter::Landscape);
    } else {
        p->setOrientation(QPrinter::Portrait);
    }

    QDomDocument doc;
    QString errMsg;
    int errLine, errColm;
    if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
    {
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        return;
    }


    // ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(doc);
    oDoc = pre.generate();
    ORPrintRender render;
    render.setPrinter(p);
    render.render(oDoc);
    render.setupPrinter(oDoc, p);


    changed();
    ui->spinCurrentPage->setValue(1);
}

QSqlDatabase PayrollReportPreview::getDb() const
{
    return db;
}

void PayrollReportPreview::setDb(const QSqlDatabase &value)
{
    db = value;
}


QString PayrollReportPreview::xml() const
{
    return m_xml;
}

void PayrollReportPreview::setXml(const QString &xml)
{
    m_xml = xml;
}


void PayrollReportPreview::on_cmdPDF_clicked()
{
    if (oDoc) {
        ORPrintRender render;
        QString pdfFileName = QFileDialog::getSaveFileName(
                    this, "Select Save Path", QDir::homePath(), "PDF Document (*.pdf)"
                    );

        if (pdfFileName.length() < 1)
            return;

        if (!pdfFileName.endsWith(".pdf"))
            pdfFileName.append(".pdf");

        if (render.exportToPDF(oDoc, pdfFileName)) {
            QFile fl(pdfFileName);
            if (fl.exists()) {
                QDesktopServices::openUrl(QUrl(pdfFileName));
            }
        }
    }
}

void PayrollReportPreview::changed()
{
    ui->spinCurrentPage->setMaximum(previewWidget->pageCount());
    ui->spinCurrentPage->setMinimum(1);
    ui->lblOf->setText("of " + QString::number(previewWidget->pageCount()));
}

void PayrollReportPreview::on_spinCurrentPage_valueChanged(int arg1)
{
    previewWidget->setCurrentPage(arg1);
}
