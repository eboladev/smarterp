#include "reportpreview.h"
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

ReportPreview::ReportPreview(QObject *parent,
			     QSqlDatabase database,
			     QString reportName,
			     QString where):
	QObject(parent)
{
	db = database;
	printer = new QPrinter(QPrinter::HighResolution);
	printer->setCreator("SmartERP");
	param = where;
	QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '" + reportName + "'");
	if (!qu.lastError().isValid()) {
		qu.last();
		QString xml = qu.record().value("report_source").toString();
		xml.replace("param_where", param);
		_xml = xml;
		QDomDocument doc;
		QString errMsg;
		int errLine, errColm;
		if (!doc.setContent(xml, &errMsg, &errLine, &errColm)) {
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
		ORPreRender pre;
		pre.setDatabase(db);
		pre.setDom(_doc);
		qDebug() << "5";
		ORODocument *oDoc = pre.generate();
		QPrintPreviewDialog *pvr = new QPrintPreviewDialog(printer, 0);
		connect (pvr, SIGNAL(paintRequested(QPrinter*)), SLOT(paintRequested(QPrinter*)));
		pvr->exec();
		qDebug() << "6";
	} else {
		DataPublics::showWarning("Fatal error: Could not generate report.\n\n" + qu.lastError().text());
	}
}

void ReportPreview::printRequested(QPrinter */*p*/)
{
	qDebug() << "a";
	ORPreRender pre;
	pre.setDatabase(db);
	pre.setDom(_doc);
	qDebug() << "b";

	ORODocument *oDoc = pre.generate();
	qDebug() << "c";
	if (oDoc) {
		qDebug() << "d";
		ORPrintRender render;
		qDebug() << "e";
		render.setPrinter(printer);
		qDebug() << "f";
		render.render(oDoc);
		qDebug() << "g";
		render.setupPrinter(oDoc, printer);
		qDebug() << "h";
	} else {
		DataPublics::showWarning("Printer Error");
	}
	qDebug() << "i";
}
