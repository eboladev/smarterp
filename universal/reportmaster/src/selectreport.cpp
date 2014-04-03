#include "selectreport.h"
#include "ui_selectreport.h"

SelectReport::SelectReport(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SelectReport)
{
	ui->setupUi(this);
}

SelectReport::~SelectReport()
{
	delete ui;
}

void SelectReport::loadReports()
{
	QSqlQuery qu = db.exec("SELECT report_name FROM report");
	if (!qu.lastError().isValid()) {
		while (qu.next())
			ui->lstReports->insertItem(ui->lstReports->count(), qu.value(0).toString());
	}
}

void SelectReport::on_lstReports_currentTextChanged(const QString &currentText)
{
	selectedReport = currentText;
}
