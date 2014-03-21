#include "reportpreview.h"
#include "ui_reportpreview.h"
#include "../OpenRPT/renderer/renderobjects.h"
#include "../OpenRPT/renderer/openreports.h"
#include "../OpenRPT/renderer/orprerender.h"
#include "../OpenRPT/renderer/orprintrender.h"
#include "parameterproperties.h"
#include "data.h"
#include "parsexmlutils.h"
#include "paramlistedit.h"
#include "../OpenRPT/renderer/previewdialog.h"
#include "../OpenRPT/common/builtinSqlFunctions.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#include <QPrintDialog>
#endif


ReportPreview::ReportPreview(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ReportPreview)
{
    ui->setupUi(this);
    db = database;

    connect (ui->actionAll_Pages, SIGNAL(triggered()), SLOT(allPages()));
    connect (ui->actionDouble_Pages, SIGNAL(triggered()), SLOT(facingPages()));
    connect (ui->actionSingle_Page, SIGNAL(triggered()), SLOT(singlePage()));

    connect (ui->actionPrint, SIGNAL(triggered()), SLOT(print()));

    connect (ui->actionZoom_In, SIGNAL(triggered()), SLOT(zoomIn()));
    connect (ui->actionZoom_Out, SIGNAL(triggered()), SLOT(zoomOut()));

    connect (ui->actionFirst_Page, SIGNAL(triggered()), SLOT(firstPage()));
    connect (ui->actionPrevious_Page, SIGNAL(triggered()), SLOT(previousPage()));
    connect (ui->actionNext_Page, SIGNAL(triggered()), SLOT(nextPage()));
    connect (ui->actionLast_Page, SIGNAL(triggered()), SLOT(lastPage()));

    printer = new QPrinter(QPrinter::HighResolution);
    m_view = new QPrintPreviewWidget(printer, this);
    setCentralWidget(m_view);

}

ReportPreview::~ReportPreview()
{
    delete ui;
}

/*!
 * \brief ReportPreview::setXML
 * \param xml
 */

void ReportPreview::setXML(QString xml)
{
    _xml = xml;
    QDomDocument doc;
    QString reportName = "Report";
    QString errMsg;
    int errLine, errColm;
    if (!doc.setContent(xml, &errMsg, &errLine, &errColm))
    {
        QMessageBox::critical(this, tr("Error Loading Report"),
                              tr("There was an error opening the report %1."
                                 "\n\n%2 on line %3 column %4.")
                              .arg(reportName).arg(errMsg).arg(errLine).arg(errColm) );
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "report") {
        QMessageBox::critical(this, tr("Not a valid file"),
                              tr("The file %1 does not appear to ba a valid file"
                                 "\n\nThe root node is not 'report'.").arg(reportName));
        return;
    }
    _doc = doc;
    connect (m_view, SIGNAL(paintRequested(QPrinter*)), SLOT(paintRequested(QPrinter*)));
    m_view->updatePreview();
    m_view->fitToWidth();
}

void ReportPreview::paintRequested(QPrinter *p)
{
    ORPreRender pre;
    pre.setDatabase(db);
    pre.setDom(_doc);

    ORODocument *oDoc = pre.generate();
    if (oDoc) {
        ORPrintRender render;
        render.setPrinter(p);
        render.render(oDoc);
        render.setupPrinter(oDoc, p);
        m_view->setCurrentPage(1);
    }
}


void ReportPreview::firstPage()
{
    m_view->setCurrentPage(1);
    viewChanged();
}

void ReportPreview::previousPage()
{
    int newPage = m_view->currentPage() - 1;
    if (newPage > 0)
        m_view->setCurrentPage(newPage);
    viewChanged();
}

void ReportPreview::nextPage()
{
    int newPage = m_view->currentPage() + 1;
    if (newPage < m_view->pageCount() + 1)
        m_view->setCurrentPage(newPage);
    viewChanged();
}

void ReportPreview::lastPage()
{
    m_view->setCurrentPage(m_view->pageCount());
    viewChanged();
}


void ReportPreview::singlePage()
{
    m_view->setViewMode(QPrintPreviewWidget::SinglePageView);
}

void ReportPreview::facingPages()
{
    m_view->setViewMode(QPrintPreviewWidget::FacingPagesView);
}

void ReportPreview::allPages()
{
    m_view->setViewMode(QPrintPreviewWidget::AllPagesView);
}

void ReportPreview::zoomIn()
{
    m_view->zoomIn();
}

void ReportPreview::zoomOut()
{
    m_view->zoomOut();
}

void ReportPreview::print()
{
    QPrintDialog *d = new QPrintDialog(printer, this);
    if (d->exec() == QDialog::Accepted) {
        m_view->print();
    }
}

void ReportPreview::viewChanged()
{
    int currentPage = m_view->currentPage();
    ui->actionFirst_Page->setEnabled(false);
    ui->actionNext_Page->setEnabled(false);
    ui->actionPrevious_Page->setEnabled(false);
    ui->actionLast_Page->setEnabled(false);

    if (currentPage > 1) {
        ui->actionPrevious_Page->setEnabled(true);
        ui->actionFirst_Page->setEnabled(true);
    }

    if (currentPage < m_view->pageCount()) {
        ui->actionNext_Page->setEnabled(true);
        ui->actionLast_Page->setEnabled(true);
    }

    //pageLabel->setText(tr("Page %1 of %2").arg(QString::number(currentPage), QString::number(m_view->pageCount())));
}
