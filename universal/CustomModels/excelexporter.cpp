#include "excelexporter.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include "excelexporter_thread.h"
#include <QMessageBox>
ExcelExporter::ExcelExporter(QObject *parent, QSqlQueryModel *model) :
	QObject(parent)
{
	m_model = model;


	QString fName = QFileDialog::getSaveFileName(0, "Select the location to save the file", QDir::homePath(), "Excel Files (*.xlsx)");
	if (fName.length() > 0) {
		pdg = new QProgressDialog(0);
		pdg->setMinimum(0);
		pdg->setMaximum(model->rowCount() * model->columnCount());
		pdg->setValue(0);
		pdg->show();
		fileName = fName;
		ExcelExporter_Thread *th = new ExcelExporter_Thread(this);
		connect (th, SIGNAL(finished()), SLOT(processingFinished()));
		connect (th, SIGNAL(progress(int)), SLOT(progress(int)));
		connect (th, SIGNAL(status(QString)), SLOT(status(QString)));
		th->setVars(m_model, fName);
		th->start();
	}
}

#include <QMessageBox>
#include <QDesktopServices>
void ExcelExporter::processingFinished()
{
	pdg->close();
	QMessageBox::information(0, "File Created", "The data has been successfully exported to: \n" + fileName);
	QDesktopServices::openUrl(fileName);
}

void ExcelExporter::status(QString s)
{
	pdg->setLabelText(s);
}

void ExcelExporter::progress(int p)
{
	pdg->setValue(p);
}
