#include "smartpreviewdialog.h"
#include "ui_smartpreviewdialog.h"
#include "orprerender.h"
#include "orprintrender.h"
#include "renderobjects.h"

#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QPrinter>
#endif

SmartPreviewDialog::SmartPreviewDialog(ORODocument *document,
				       QPrinter *pPrinter,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SmartPreviewDialog)
{
	ui->setupUi(this);

	connect (ui->cmdZoomIn, SIGNAL(clicked())
		 , ui->previewWidget, SLOT(zoomIn()));
	connect (ui->cmdZoomOut, SIGNAL(clicked())
		 , ui->previewWidget, SLOT(zoomOut()));

	ui->previewWidget->loadReport(document, pPrinter);
}

SmartPreviewDialog::~SmartPreviewDialog()
{
	delete ui;
}

void SmartPreviewDialog::on_cmdPrint_clicked()
{
	this->accept();
}
