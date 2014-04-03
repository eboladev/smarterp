#include "htmlreportpreview.h"
#include "ui_htmlreportpreview.h"
#include <QTextDocument>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif

HTMLReportPreview::HTMLReportPreview(QWidget *parent, QSqlDatabase database, QSqlQuery query, QString title, bool firstColumnHidden, QString reportQuery, QStringList columnsToSum) :
	QMainWindow(parent),
	ui(new Ui::HTMLReportPreview)
{
	ui->setupUi(this);
	rawHtml = false;
	db = database;

	sumColumns = columnsToSum;

	if (!db.isOpen()) {
		db.open();
	}

	qu = query;

	s_title = title;
	hideFirstColumn = firstColumnHidden;
	s_query = reportQuery;

	initGui();
}

HTMLReportPreview::HTMLReportPreview(QWidget *parent, QSqlDatabase database,
				     QString query, QString title,
				     bool firstColumnHidden, QString reportQuery,
				     QStringList columnsToSum)
{
	QSqlQuery q2u = db.exec(query);
	HTMLReportPreview(parent, database, qu, title, firstColumnHidden, reportQuery, columnsToSum);
}

HTMLReportPreview::HTMLReportPreview(QWidget *parent, QString html) :
	QMainWindow(parent),
	ui(new Ui::HTMLReportPreview)
{
	ui->setupUi(this);
	rawHtml = true;
	s_rawHtml = html;
	initGui();
}


HTMLReportPreview::~HTMLReportPreview()
{
	delete ui;
}

void HTMLReportPreview::initGui()
{
	QMessageBox::information(this, "This", "This");
	printer = new QPrinter(QPrinter::HighResolution);
	previewWidget = new QPrintPreviewWidget(printer, this);

	this->setCentralWidget(previewWidget);

	orientationGroup = new QActionGroup(this);
	orientationGroup->addAction(ui->actionLandscape);
	orientationGroup->addAction(ui->actionPortrait);

	ui->actionLandscape->setCheckable(true);
	ui->actionPortrait->setCheckable(true);

	ui->actionLandscape->setChecked(true);

	previewWidget->setOrientation(QPrinter::Landscape);

	connect (previewWidget, SIGNAL(previewChanged()), this, SLOT(viewChanged()));
	connect (ui->actionZoom_In, SIGNAL(triggered()), previewWidget, SLOT(zoomIn()));
	connect (ui->actionZoom_Out, SIGNAL(triggered()), previewWidget, SLOT(zoomOut()));
	connect (ui->actionAll_Pages, SIGNAL(triggered()), previewWidget, SLOT(setAllPagesViewMode()));
	connect (ui->actionSingle_Page, SIGNAL(triggered()), previewWidget, SLOT(setSinglePageViewMode()));
	connect (ui->actionFacing_Pages, SIGNAL(triggered()), previewWidget, SLOT(setFacingPagesViewMode()));
	connect (ui->actionLandscape, SIGNAL(triggered()), previewWidget, SLOT(setLandscapeOrientation()));
	connect (ui->actionPortrait, SIGNAL(triggered()), previewWidget, SLOT(setPortraitOrientation()));
	connect (ui->actionPage_Setup, SIGNAL(triggered()), SLOT(actionPageSetup()));
	connect (ui->actionPrint, SIGNAL(triggered()), SLOT(actionPrint()));
	connect (ui->actionPrevious_Page, SIGNAL(triggered()), SLOT(previousPage()));
	connect (ui->actionFirst_Page, SIGNAL(triggered()), SLOT(firstPage()));
	connect (ui->actionNext_Page, SIGNAL(triggered()), SLOT(nextPage()));
	connect (ui->actionLast_Page, SIGNAL(triggered()), SLOT(lastPage()));

	connect (previewWidget, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)));

	printer->setPageMargins(0.1,0.1,0.1,0.1,QPrinter::Inch);

}

void HTMLReportPreview::print(QPrinter *printer)
{
	QString html = "";
	if (rawHtml) {
		html = s_rawHtml;
	} else {
		//QSqlQuery qu = db.exec("SELECT * FROM report_ocregister LIMIT 0,200");
		qu = db.exec(s_query);
		qDebug() << s_query;
		printer->setOrientation(QPrinter::Landscape);
		//Add Heading
		html += "<h1>" + s_title + "</h1>";
		//Start Table
		html += "<table width=100% Border=1 CellSpacing=0 CellPadding=0>";
		//Add Header
		html += "<tr bgcolor=\"lightgray\">";

		int start = 0;
		if (hideFirstColumn)
			start = 1;

		for (int i = start; i < qu.record().count(); i++) {
			html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
		}
		html += "</tr>";
		//Add Body
		int cnt = 0;
		while (qu.next()) {
			cnt = cnt + 1;
			//        if (cnt == 0) {
			//            if (qu.record().count() > 4) {
			//                printer->setOrientation(QPrinter::Landscape);
			//            }
			//        }
			html += "<tr>";
			for (int i = start; i < qu.record().count(); i++) {
				QSqlRecord rec = qu.record();
				QString txt = rec.value(i).toString();

				if (sumColumns.contains(qu.record().fieldName(i))) {
					txt = QLocale(QLocale::English).toString(txt.toDouble());
					html += "<td align=right>" + txt + "</td>";
				} else {
					html += "<td>" + txt + "</td>";
				}
			}
			html += "</tr>";
		}
		//Add Sum row
		html += "<tr bgcolor=\"lightgray\">";

		for (int i = start; i < qu.record().count(); i++) {
			QString sumText = "";
			if (sumColumns.contains(qu.record().fieldName(i))) {
				float sum = 0;

				QSqlQuery sumQuery = qu;
				sumQuery.seek(-1);

				while (sumQuery.next()) {
					QString thisColText = qu.record().value(qu.record().fieldName(i)).toString();
					float thisSum = QString::number(thisColText.toFloat(), 'f', 2).toFloat();
					thisSum = qRound(thisSum);
					//sum = sum + thisColText.toLong();
					sum = sum + thisSum;
					//
				}
				qDebug() << qRound64(sum);
				//sumText = QString::number(qRound64(sum), 'f', 0);  //QString::number(sum); //QLocale(QLocale::English).toString((double)sum);
				sumText = QLocale(QLocale::English).toString(sum, 'f', 0);
			}
			html += "<td align=right><b>" + sumText + "</b></td>";
		}
		//        //Add Footer Column Heads
		//        html += "<tr bgcolor=\"lightgray\">";

		//        for (int i = start; i < qu.record().count(); i++) {
		//            html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
		//        }
		//        html += "</tr>";
		//Close table
		html += "</table>";
		html += "<br/>";
		html += "<br/>";
		html += "<br/>";
		//Add Footer

		html += "Report Generated On " + QDate::currentDate().toString("dd-MMM-yyyy") + " at " + QTime::currentTime().toString("hh:mm:ss");
	}
	QTextDocument *doc = new QTextDocument(this);
	doc->setHtml(html);
	doc->print(printer);

}

void HTMLReportPreview::actionPrint()
{
	QPrintDialog *prnt = new QPrintDialog(printer, this);
	if (prnt->exec() == QDialog::Accepted) {
		previewWidget->print();
	}
}

void HTMLReportPreview::actionPageSetup()
{
	QPageSetupDialog *set = new QPageSetupDialog(printer, previewWidget);
	if (set->exec() == QDialog::Accepted) {
		if (previewWidget->orientation() == QPrinter::Portrait) {
			ui->actionPortrait->setChecked(true);
			previewWidget->setPortraitOrientation();
		}else {
			ui->actionLandscape->setChecked(true);
			previewWidget->setLandscapeOrientation();
		}
	}
}

void HTMLReportPreview::firstPage()
{
	previewWidget->setCurrentPage(1);
	viewChanged();
}

void HTMLReportPreview::previousPage()
{
	if (previewWidget->currentPage() > 1)
		previewWidget->setCurrentPage(previewWidget->currentPage() - 1);
	viewChanged();
}

void HTMLReportPreview::nextPage()
{
	if (previewWidget->currentPage() < previewWidget->pageCount())
		previewWidget->setCurrentPage(previewWidget->currentPage() + 1);
	viewChanged();
}

void HTMLReportPreview::lastPage()
{
	previewWidget->setCurrentPage(previewWidget->pageCount());
}

void HTMLReportPreview::viewChanged()
{
	ui->actionFirst_Page->setEnabled(false);
	ui->actionLast_Page->setEnabled(false);
	ui->actionPrevious_Page->setEnabled(false);
	ui->actionNext_Page->setEnabled(false);

	if (previewWidget->currentPage() > 1) {
		ui->actionFirst_Page->setEnabled(true);
		ui->actionPrevious_Page->setEnabled(true);
	}

	if (previewWidget->currentPage() < previewWidget->pageCount()) {
		ui->actionNext_Page->setEnabled(true);
		ui->actionLast_Page->setEnabled(true);
	}

}
