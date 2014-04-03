#include "mainwindow.h"
#include "../reportmaster/tmp/ui_mainwindow.h"

#include <QMessageBox>
#include <QInputDialog>


#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QDesktopServices>

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

#include "selectreport.h"
#include "selectdaterange.h"
#include "datapublics.h"
#include "qtprinter.h"
MainWindow::MainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//    ui->menuBar->setStyleSheet("QToolButton { border-image: url(:/images/panel_button.png) 2 2 2 19;"
	//                               " border-width: 2px 2px 2px 19px; padding-left: -17; padding-right: 4 } "
	//                               "QToolButton:checked { border-image: url(:/images/panel_button_checked.png) 2 2 2 19 } "
	//                               "QToolButton::menu-indicator { width:0; height:0 }"
	//                           #ifndef Q_WS_MAC // Mac UIs usually don't hover
	//                               "QToolButton:checked:hover { border-image: url(:/images/panel_button_checked_hover.png) 2 2 2 19 } "
	//                               "QToolButton:pressed:hover { border-image: url(:/images/panel_button_pressed.png) 2 2 2 19 } "
	//                               "QToolButton:hover { border-image: url(:/images/panel_button_hover.png) 2 2 2 19 } "
	//                           #endif
	//                               );

	zoomLabel = new QLabel(this);
	pageLabel = new QLabel(this);
	ui->statusBar->addWidget(zoomLabel);
	ui->statusBar->insertWidget(1, pageLabel);
	hasDate = false;
	isreloading = false;
	printer = new QPrinter(QPrinter::HighResolution);
	m_view = new QPrintPreviewWidget(printer, this);

	//this->setCentralWidget(m_view);
	ui->verticalLayout->addWidget(m_view);
	m_view->setVisible(true);

	//db = DataPublics::getDatabase("ReportsConnection", "reports");
	//db.open();
	db = database;

	connect (ui->actionAbout_Qt, SIGNAL(triggered()), SLOT(helpAboutQt()));
	connect (ui->actionAbout_Report_Master, SIGNAL(triggered()), SLOT(helpAbout()));
	connect (ui->actionOpen_Report, SIGNAL(triggered()), SLOT(selectDbReport()));

	connect (ui->actionFirst_Page, SIGNAL(triggered()), SLOT(firstPage()));
	connect (ui->actionPrevious_Page, SIGNAL(triggered()), SLOT(previousPage()));
	connect (ui->actionNext_Page, SIGNAL(triggered()), SLOT(nextPage()));
	connect (ui->actionLast_Page, SIGNAL(triggered()), SLOT(lastPage()));

	connect (m_view, SIGNAL(previewChanged()), SLOT(viewChanged()));
	connect (ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	connect (ui->actionZoom_In, SIGNAL(triggered()), m_view, SLOT(zoomIn()));
	connect (ui->actionZoom_Out, SIGNAL(triggered()), m_view, SLOT(zoomOut()));
	connect (ui->actionLandscape_Mode, SIGNAL(triggered()), m_view, SLOT(setLandscapeOrientation()));
	connect (ui->actionPotrait_Mode, SIGNAL(triggered()), m_view, SLOT(setPortraitOrientation()));
	connect (ui->actionFit_Page, SIGNAL(triggered()), m_view, SLOT(fitInView()));
	connect (ui->actionFit_Width, SIGNAL(triggered()), m_view, SLOT(fitToWidth()));

	connect (ui->actionSingle_Page, SIGNAL(triggered()), SLOT(singlePage()));
	connect (ui->actionDouble_Pages, SIGNAL(triggered()), SLOT(facingPages()));
	connect (ui->actionAll_Pages, SIGNAL(triggered()), SLOT(allPages()));



	ui->toolBar->setVisible(true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::helpAboutQt()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::helpAbout()
{
	QMessageBox::about(this, "Report Master", "Report Master 2.0\n\n(c)J. W. Joshua 2012");
}

#include "publicprinter.h"
void MainWindow::loadReport(QString reportName)
{
	name = reportName;
	QSqlQuery rq = db.exec("SELECT * FROM report WHERE report_name= '" + reportName + "' ORDER BY report_grade DESC");

	if (rq.lastError().isValid()) {
		QMessageBox::critical(this, "Report Error", "Database Error\n" + rq.lastError().text());
		return;
	}
	rq.first();



	QString reportContent = rq.record().value("report_source").toString();




	QString reportQuery = "";
	QString reportSubstitute = "";

	//list of all reports with a date range
	if (reportName == "OCRegister" || reportName == "ProductionTrail" || reportName == "CorrugatorAnalysis"
	    || reportName == "ClientTonnageDetail"
	    ) {
		//if (!getDateRange(StartDate, EndDate, isRange))
		//    return;
		if (!isreloading) {
			SelectDateRange sel(this);
			hasDate = false;
			if (sel.exec()) {
				StartDate = sel.startDate.toString("yyyy-MM-dd");
				EndDate = sel.endDate.toString("yyyy-MM-dd");
				isRange = sel.isRange;
				hasDate = true;
			} else {
				return;
			}
		}

		if (!hasDate)
			return;

		if (!isRange)
			EndDate = StartDate;

		if (reportName == "CorrugatorAnalysis") {
			db.exec("CALL StartOcRecalculation('" + StartDate + "', '" + EndDate + "')");
		}

		reportSubstitute = " WHERE `Date` = '" + StartDate + "' ";
		if (isRange)
			reportSubstitute = " WHERE `Date` BETWEEN '" + StartDate + "' AND '" + EndDate + "' ";

		//if (!isRange)
		//    reportSubstitute = "";
	}
	reportQuery = rq.record().value("code_query").toString();
	reportQuery.replace("param_where", reportSubstitute);
	reportContent.replace("param_query", reportQuery);
	//DataPublics::showInformation(reportQuery);

	if (reportName == "CorrugatorAnalysis") {
		reportContent.replace("param_where", reportSubstitute);
	}

	loadReportXML(reportContent);
}

void MainWindow::selectDbReport()
{
	SelectReport sel(this);
	sel.db = db;
	sel.loadReports();
	if (sel.exec() == QDialog::Accepted) {
		if (sel.selectedReport.length() > 0) {
			isreloading = false;
			loadReport(sel.selectedReport);
		}
	}
}

void MainWindow::paintRequested(QPrinter *p)
{
	ORPreRender pre;
	pre.setDatabase(db);
	pre.setDom(_doc);

	ORODocument *oDoc = pre.generate();
	if (!oDoc)
		return;

	ORPrintRender render;
	render.setPrinter(p);
	render.render(oDoc);
	render.setupPrinter(oDoc, p);

	m_view->setCurrentPage(1);

}

void MainWindow::firstPage()
{
	m_view->setCurrentPage(1);
	viewChanged();
}

void MainWindow::previousPage()
{
	int newPage = m_view->currentPage() - 1;
	if (newPage > 0)
		m_view->setCurrentPage(newPage);
	viewChanged();
}

void MainWindow::nextPage()
{
	int newPage = m_view->currentPage() + 1;
	if (newPage < m_view->pageCount() + 1)
		m_view->setCurrentPage(newPage);
	viewChanged();
}

void MainWindow::lastPage()
{
	m_view->setCurrentPage(m_view->pageCount());
	viewChanged();
}

void MainWindow::loadReportXML(QString xml)
{

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

void MainWindow::viewChanged()
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

	pageLabel->setText(tr("Page %1 of %2").arg(QString::number(currentPage), QString::number(m_view->pageCount())));
}

void MainWindow::singlePage()
{
	m_view->setViewMode(QPrintPreviewWidget::SinglePageView);
}

void MainWindow::facingPages()
{
	m_view->setViewMode(QPrintPreviewWidget::FacingPagesView);
}

void MainWindow::allPages()
{
	m_view->setViewMode(QPrintPreviewWidget::AllPagesView);
}

bool MainWindow::getDateRange(QString start, QString end, bool isRange)
{
	Q_UNUSED(isRange);
	SelectDateRange selWindow(this);

	if (!selWindow.exec() == QDialog::Accepted)
		return false;

	start = selWindow.startDate.toString("yyyy-MM-dd");
	end = selWindow.endDate.toString("yyyy-MM-dd");
	isRange = selWindow.isRange;
	return true;
}

void MainWindow::on_actionReload_triggered()
{
	if (name.length() > 0) {
		isreloading = true;
		loadReport(name);
	} else {
		selectDbReport();
	}
}

void MainWindow::on_actionGenerate_Report_From_SQL_triggered()
{
	LoadReportFromSQL *ldb = new LoadReportFromSQL(this, db);
	if (ldb->exec() == QDialog::Accepted) {
		QString reportXML = DataPublics::getReportXML(ldb->query, ldb->title, db, ldb->lines, ldb->landscape, ldb->pageNumbers, false);
		loadReportXML(reportXML);
		if (ldb->save) {
			QSqlQuery qu = db.exec(tr("INSERT INTO report (report_name, report_descrip, report_grade, report_source, report_query, code_query) VALUES ('%1', '%2', '%3', '%4', '%5', '%6')")
					       .arg(ldb->title, ldb->title, "1", reportXML, ldb->query, ldb->query));
			if (!qu.lastError().isValid()) {
				DataPublics::showInformation("Report Saved");
			} else {
				DataPublics::showWarning("There was an error while saving the report.\n\n" + qu.lastError().text());
			}
		}
	}
}

void MainWindow::on_actionPrint_triggered()
{
	bool showPreview = false;

	ORPreRender pre;
	pre.setDatabase(db);
	pre.setDom(_doc);

	ORODocument *doc = pre.generate();
	if (!doc)
		return;

	QPrinter printer(QPrinter::HighResolution);

	ORPrintRender render;
	render.setupPrinter(doc, &printer);

	if(showPreview)
	{
		if(printer.printerName().isEmpty()) { // no default printer
			QPrintDialog pd(&printer);
			if(pd.exec() != QDialog::Accepted)
			{
				return; // no printer, can't preview
			}
		}

		PreviewDialog preview (doc, &printer, this);
		if (preview.exec() == QDialog::Rejected)
			return;
	}

	QPrintDialog pd(&printer);
	pd.setMinMax(1, doc->pages());
	if(pd.exec() == QDialog::Accepted)
	{
		render.setPrinter(&printer);
		render.render(doc);
	}
	delete doc;
}

void MainWindow::on_actionPDF_triggered()
{
	printer->setOutputFormat(QPrinter::PdfFormat);
	QString fileName = QFileDialog::getSaveFileName(this, "Save PDF As...", QDir::homePath());
	if (fileName.length() > 0) {
		if (!fileName.endsWith(".pdf"))
			fileName.append(".pdf");

		printer->setOutputFileName(fileName);
		m_view->print();

		int res =  QMessageBox::question(this, "File Saved", "<b>" + fileName + "</b> successfully saved.<br/>Would you like to open it now?",
						 QMessageBox::Yes, QMessageBox::No);
		if (res == QMessageBox::Yes) {
			QFile fl(fileName);
			if (fl.exists()) {
				QDesktopServices::openUrl(fileName);
			}
		}
	}
}

#include "htmlreportpreview.h"
void MainWindow::on_actionOrder_Qty_Trail_triggered()
{
	QDate sDate = QDate::currentDate().addDays(-1);
	QDate eDate  = QDate::currentDate();

	SelectDateRange *sd = new SelectDateRange(this);
	if (sd->exec() == QDialog::Accepted) {
		sDate = sd->startDate;
		eDate = sd->endDate;
	}

	QSqlQuery qu2 =  db.exec("CALL cartons.recalculateordertrail('" + sDate.toString("yyyy-MM-dd") + "', '" + eDate.toString("yyyy-MM-dd") + "');");
	if (qu2.lastError().isValid()) {
		DataPublics::showWarning(qu2.lastError().text());
	} else {
		QString query = "SELECT * FROM cartons.vw_ordertrail";
		HTMLReportPreview *pv = new HTMLReportPreview(this, db, query, "Order Trail (" + sDate.toString("dd MMM yyyy") + " - " + eDate.toString("dd MMM yyyy") + ")", false, query, QStringList());
		pv->show();
	}
}

void MainWindow::on_actionDetailed_Order_Trail_triggered()
{
	QDate sDate = QDate::currentDate().addDays(-1);
	QDate eDate  = QDate::currentDate();

	SelectDateRange *sd = new SelectDateRange(this);
	if (sd->exec() == QDialog::Accepted) {
		sDate = sd->startDate;
		eDate = sd->endDate;
	}

	QSqlQuery qu2 =  db.exec("CALL cartons.recalculateordertrail('" + sDate.toString("yyyy-MM-dd") + "', '" + eDate.toString("yyyy-MM-dd") + "');");
	if (qu2.lastError().isValid()) {
		DataPublics::showWarning(qu2.lastError().text());
	} else {
		QString query = "SELECT * FROM cartons.vw_ordertrail_ex";
		HTMLReportPreview *pv = new HTMLReportPreview(0, db, query, "Order Trail (" + sDate.toString("dd MMM yyyy") + " - " + eDate.toString("dd MMM yyyy") + ")", false, query, QStringList());
		pv->show();
	}
}


