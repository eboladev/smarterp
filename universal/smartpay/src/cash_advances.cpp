#include "cash_advances.h"
#include "ui_cash_advances.h"
#include "datapublics.h"
CashAdvances::CashAdvances(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::CashAdvances)
{
	ui->setupUi(this);
	db = database;
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
}

CashAdvances::~CashAdvances()
{
	delete ui;
}

void CashAdvances::on_cboMonths_currentIndexChanged(const QString &arg1)
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + arg1 + "'", db, "MonthID").toString();
	if (monthID.length() > 0) {
		QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
		QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();
		QString query = "SELECT "
				"employee_cash_advances.AdvanceID "
				", vw_employeenames_ex.Name "
				", employee_cash_advances.AdvanceDate "
				", employee_cash_advances.Amount "
				"FROM "
				"vw_employeenames_ex "
				"INNER JOIN employee_cash_advances  "
				"ON (vw_employeenames_ex.employeeID = employee_cash_advances.EmployeeID) "
				" WHERE employee_cash_advances.AdvanceDate BETWEEN '" + startDate + "'"
				" AND '" + endDate + "'";
		////qDebug() << query;
		ui->lstCashAdvances->setQuery(query, db, "CashAdvances for " + ui->cboMonths->currentText(), true);
		ui->lstCashAdvances->setColumnHidden(0, true);
	}
}

#include "cashadvanceswizard.h"
void CashAdvances::on_actionNew_Advance_triggered()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}

	CashAdvancesWizard *wiz = new CashAdvancesWizard(this, db);
	if (wiz->exec() == QDialog::Accepted) {
		on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
	}
}

void CashAdvances::on_cmdDelete_clicked()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}
	QString id = ui->lstCashAdvances->getCurrentID();
	if (id.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM employee_cash_advances WHERE AdvanceID = '" + id + "'");
			on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
		}
	}
}

void CashAdvances::on_actionRefresh_triggered()
{
	on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
}
