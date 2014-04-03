#ifndef SMARTOCPRINTER_H
#define SMARTOCPRINTER_H

#include <QDialog>
#include <QPrinter>
#include <QWidget>
#include <QtXml>

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
#include "smartocprinter.h"
#include <QtSql>

namespace Ui {
class SmartOcPrinter;
}

class SmartOcPrinter : public QDialog
{
	Q_OBJECT

public:
	explicit SmartOcPrinter(QDomDocument doc = QDomDocument(),
				QSqlDatabase database = QSqlDatabase(),
				QWidget *parent = 0);
	~SmartOcPrinter();
private slots:
	void zoomIn();
	void zoomOut();
	void print();
	void makePDF();
	void previewRequested(QPrinter *prnt);
private:
	Ui::SmartOcPrinter *ui;
	QPrinter *printer;
	QDomDocument _doc;
	QSqlDatabase db;
};

#endif // SMARTOCPRINTER_H
