#include "advances.h"
#include "ui_advances.h"
#include "datapublics.h"
Advances::Advances(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Advances)
{
	ui->setupUi(this);
	db = database;
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
}

Advances::~Advances()
{
	delete ui;
}

void Advances::on_cboMonths_currentIndexChanged(const QString &arg1)
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + arg1 + "'", db, "MonthID").toString();
	if (monthID.length() > 0) {
		QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
		QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();
		QString query = "SELECT * FROM vw_bank_advances"
				" WHERE AdvanceDate BETWEEN '" + startDate + "'"
				" AND '" + endDate + "'";
		////qDebug() << query;
		ui->lstAdvances->setQuery(query, db, "Advances for " + ui->cboMonths->currentText(), true);
		ui->lstAdvances->setColumnHidden(0, true);
	}
}

#include "advanceswizard.h"
void Advances::on_actionNew_Advance_triggered()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}

	AdvancesWizard *wiz = new AdvancesWizard(this, db);
	if (wiz->exec() == QDialog::Accepted) {
		on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
	}
}

void Advances::on_cmdDelete_clicked()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}
	QString id = ui->lstAdvances->getCurrentID();
	if (id.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM employee_advances WHERE AdvanceID = '" + id + "'");
			if (db.lastError().isValid())
				DataPublics::showWarning(db.lastError().text());
			on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
		}
	}
}

void Advances::on_actionRefresh_triggered()
{
	on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
}
