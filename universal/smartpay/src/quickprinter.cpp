#include "quickprinter.h"
#include <QPrintPreviewDialog>
#include <QTextDocument>
//#include "renderobjects.h"
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
QuickPrinter::QuickPrinter(QObject *parent, QString reportName, QString where, QSqlDatabase database, bool createPdf) :
	QObject(parent)
{
	setIsPdf(createPdf);
	m_reportName = reportName;
	m_where = where;
	db  = database;
	printer = new QPrinter(QPrinter::ScreenResolution);
	printer->setCreator("SmartPay");

	QSqlQuery qu = db.exec("SELECT * FROM report WHERE report_name = '" + m_reportName + "'");
	if (!qu.lastError().isValid()) {
		qu.last();
		QString xml = qu.record().value("report_source").toString();
		xml.replace("param_where", m_where);
		xml.replace("Helvetica", "Tahoma");
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
		ORPreRender pre;
		pre.setDatabase(db);
		pre.setDom(_doc);
		ORODocument *oDoc = pre.generate();
		QPrintPreviewDialog *pvr = new QPrintPreviewDialog(printer, 0);
		connect (pvr, SIGNAL(paintRequested(QPrinter*)), SLOT(paintRequested(QPrinter*)));
		pvr->exec();
	}else {
		DataPublics::showWarning("Fatal error: Could not generate report.\n\n" + qu.lastError().text());
	}
}

bool QuickPrinter::isPdf() const
{
	return m_isPdf;
}

void QuickPrinter::setIsPdf(bool isPdf)
{
	m_isPdf = isPdf;
}

void QuickPrinter::paintRequested(QPrinter *p)
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
	} else {
		DataPublics::showWarning("Printer Error");
	}
}
