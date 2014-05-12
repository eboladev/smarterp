#include "publicprinter.h"
#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrintPreviewDialog>
#endif
#if QT_VERSION < 0x50000
#include <QPrintPreviewDialog>
#endif

#include <QTextDocument>
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
#include <QMessageBox>
#include <QDebug>

PublicPrinter::PublicPrinter(QWidget *parent, QSqlDatabase database, QString where, QString report) :
	QObject(parent)
{
	db = database;
	param = where;
	reportName = report;
	printer = new QPrinter(QPrinter::HighResolution);
	printer->setCreator("Megvel Cartons Ltd ERP");
	printer->setDocName(report);

	printer->setOutputFormat(QPrinter::NativeFormat);

	QPrintPreviewDialog *dg = new QPrintPreviewDialog(printer, parent, Qt::Window);
	dg->setLocale(QLocale::English);
	connect (dg, SIGNAL(paintRequested(QPrinter*)), SLOT(printRequested(QPrinter *)));

	QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '"  + reportName + "'");
	if (!qu.lastError().isValid()) {
		qu.last();
		QString xml = qu.record().value("report_source").toString();
		if (xml.contains("<sql>param_query</sql>")) {
			QString rptQuery = qu.record().value("code_query").toString();
			rptQuery.replace("param_where", where);
			xml.replace("param_query", rptQuery);
		} else {
			xml.replace("param_where", where);
		}
		////qDebug() << xml;
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
	}

	dg->exec();
}

void PublicPrinter::printRequested(QPrinter *p)
{
	Q_UNUSED(p);
	ORPreRender pre;
	pre.setDatabase(db);
	pre.setDom(_doc);

	ORODocument *oDoc = pre.generate();
	if (oDoc) {
		ORPrintRender render;
		render.setPrinter(printer);
		render.render(oDoc);
		render.setupPrinter(oDoc, printer);
		//printer->setOutputFormat(QPrinter::PdfFormat);
	}
}
