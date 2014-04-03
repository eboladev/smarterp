#ifndef PAYROLLREPORTPREVIEW_H
#define PAYROLLREPORTPREVIEW_H

#include <QWidget>
#include <QPrinter>
#include <QtSql>
#include <QPrintPreviewWidget>
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
namespace Ui {
class PayrollReportPreview;
}

class PayrollReportPreview : public QWidget
{
	Q_OBJECT

public:
	explicit PayrollReportPreview(QWidget *parent = 0,
				      QPrinter *p = new QPrinter()
			);
	~PayrollReportPreview();

	QPrinter *printer() const;
	void setPrinter(QPrinter *printer);
	void setVars(ORPreRender pr, ORODocument *doc);

	QString xml() const;
	void setXml(const QString &xml);

	QSqlDatabase getDb() const;
	void setDb(const QSqlDatabase &value);

public slots:
	void showPreview();

signals:
	void previewRequested(QPrinter *p);

private slots:
	void on_cmdZoomIn_clicked();
	void on_cmdZoomOut_clicked();
	void on_cmdPrint_clicked();
	void printRequesed(QPrinter *pr);
	void drawReport(QPrinter *p);
	void on_cmdPDF_clicked();
	void changed();
	void on_spinCurrentPage_valueChanged(int arg1);

private:
	Ui::PayrollReportPreview *ui;
	QPrinter * m_printer;
	QPrintPreviewWidget *previewWidget;

	ORPreRender pre;
	ORODocument *oDoc;

	QString m_xml;
	QSqlDatabase db;
};

#endif // PAYROLLREPORTPREVIEW_H
