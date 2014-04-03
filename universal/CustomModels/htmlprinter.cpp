#include "htmlprinter.h"
#include <QTextDocument>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrintPreviewDialog>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrintPreviewDialog>
#endif

HtmlPrinter::HtmlPrinter(QObject *parent, QSqlDatabase database, QString sqlQuery, QString reportTitle) :
	QObject(parent)
{
	db = database;
	sql = sqlQuery;
	title = reportTitle;
	qu = db.exec(sql);
	printer = new QPrinter(QPrinter::HighResolution);
	printer->setDocName(title);
	printer->setCreator("Smart ERP");
	printer->setOutputFileName(title);



	QPrintPreviewDialog *dg = new QPrintPreviewDialog(printer, 0, Qt::Window);
	connect (dg, SIGNAL(paintRequested(QPrinter*)), SLOT(printRequested(QPrinter*)));

	dg->showMaximized();
}

void HtmlPrinter::printRequested(QPrinter *printer)
{
	QString html = "<html><head><title>" +  title +"</title></head><body>";
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
	QTextDocument *doc = new QTextDocument(this);
	printer->setDocName(title);
	printer->setCreator("Smart ERP");
	printer->setOutputFileName(title);
	doc->setHtml(html);
	doc->print(printer);
}
