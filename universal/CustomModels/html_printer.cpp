#include "html_printer.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrintPreviewDialog>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrintPreviewDialog>
#endif
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
#include "../OpenRPT/common/builtinSqlFunctions.h"

HTML_PRINTER::HTML_PRINTER(QWidget *parent, QSqlDatabase database, QString sqlQuery, QString reportTitle) :
	QObject(parent)
{
	par = parent;
	db = database;
	sql = sqlQuery;
	title = reportTitle;
	qu = db.exec(sql);
	isRaw = false;
	initVariables();
}

HTML_PRINTER::HTML_PRINTER(QWidget *parent, QString rpt_title, QString html)
{
	par = parent;
	isRaw = true;
	title = rpt_title;
	rawHtml = html;
	initVariables();
}

void HTML_PRINTER::printRequested(QPrinter *printer)
{
	QString html = "";
	if (isRaw) {
		html = rawHtml;
	} else {
		html = "<html><head><title>" +  title +"</title></head><body>";
		html += "<h2>" + title + "</h2>";
		bool hideFirstColumn = false;
		html += "<br/>";
		html += "Report Printed On " + QDate::currentDate().toString("dd MMM yyyy");
		html += "<br/>";
		html += "<table width=100% Border=1 CellSpacing=0 CellPadding=0>";
		//Add table Header
		html += "<tr bgcolor=\"lightgray\">";

		int start = 0;
		if (hideFirstColumn)
			start = 1;

		for (int i = start; i < qu.record().count(); i++) {
			html += "<td><b>" + qu.record().fieldName(i) + "</b></td>";
		}
		html += "</tr>";
		//Add table Body
		int cnt = 0;
		while (qu.next()) {
			cnt = cnt + 1;
			html += "<tr>";
			for (int i = start; i < qu.record().count(); i++) {
				QSqlRecord rec = qu.record();
				QString txt = rec.value(i).toString();
				html += "<td>" + txt + "</td>";
			}
			html += "</tr>";
		}
		html  += "</body></html>";
	}
	QTextDocument *doc = new QTextDocument(this);
	printer->setDocName(title);
	printer->setCreator("Smart Erp Reporting Module");
	printer->setOutputFileName(title);
	doc->setHtml(html);
	doc->print(printer);
}

void HTML_PRINTER::initVariables()
{
	printer = new QPrinter(QPrinter::HighResolution);
	printer->setDocName(title);
	printer->setCreator("Smart Erp Reporting Module");
	printer->setOutputFileName(title);
	printer->setOrientation(QPrinter::Landscape);
	QPrintPreviewDialog *dg = new QPrintPreviewDialog(printer, par, Qt::Window);
	connect (dg, SIGNAL(paintRequested(QPrinter*)), SLOT(printRequested(QPrinter*)));
	dg->resize(par->width() * 1.6, par->height() * 1.6);
	dg->showMaximized();
}


void DbPrinter::printRequested(QPrinter *printer)
{
	ORPreRender pre;
	pre.setDatabase(db);
	pre.setDom(_doc);

	ORODocument *oDoc = pre.generate();
	if (oDoc) {
		ORPrintRender render;
		render.setPrinter(printer);
		render.render(oDoc);
		render.setupPrinter(oDoc, printer);
	}
}



DbPrinter::DbPrinter(QWidget *parent, QSqlDatabase database, QString reportName, QString param) :
	QObject(parent)
{
	Q_UNUSED(param);
	printer = new QPrinter(QPrinter::HighResolution);
	printer->setCreator("Athena Shift Scheduler");
	db = database;QPrintPreviewDialog *dg = new QPrintPreviewDialog(printer, parent, Qt::Window);
	connect (dg, SIGNAL(paintRequested(QPrinter*)), SLOT(printRequested(QPrinter*)));

	QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '" + reportName + "'");
	if (!qu.lastError().isValid()) {
		qu.last();
		QString xml = qu.record().value("report_source").toString();
		_xml = xml;
		QDomDocument doc;
		QString reportName = "Report";
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
	}
	dg->resize(parent->width() * 1.6, parent->height() * 1.6);

	dg->showMaximized();
}
