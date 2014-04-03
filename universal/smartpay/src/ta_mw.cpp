#include "ta_mw.h"
#include "ui_ta_mw.h"
#include "datapublics.h"
TaMW::TaMW(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::TaMW)
{
	ui->setupUi(this);
	db = database;
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
}

TaMW::~TaMW()
{
	delete ui;
}

void TaMW::on_cboMonths_editTextChanged(const QString &arg1)
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + arg1 + "'", db, "MonthID").toString();
	if (monthID.length() > 0) {
		//QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
		//QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();
		QString query = "SELECT "
				"ta.EntryID "
				", vw_employeenames_ex.Name "
				", ta.Amount "
				"FROM "
				"vw_employeenames_ex "
				"INNER JOIN ta  "
				"ON (vw_employeenames_ex.employeeID = ta.EmployeeID) "
				" WHERE ta.MonthID =  '" + monthID + "'";
		//qDebug() << query;
		ui->lstLeaves->setQuery(query, db, "Travelling Allowance Issued for " + ui->cboMonths->currentText(), true);
		ui->lstLeaves->setColumnHidden(0, true);
	}
}

#include "tawizard.h"
void TaMW::on_actionNew_triggered()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}
	TAWizard *wiz = new TAWizard(this, db);
	if (wiz->exec() == QDialog::Accepted) {
		on_cboMonths_editTextChanged(ui->cboMonths->currentText());
	}
}

void TaMW::on_cmdDelete_clicked()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
	if (closed == "Yes") {
		DataPublics::showWarning("This month has already been closed.");
		return;
	}
	QString id = ui->lstLeaves->getCurrentID();
	if (id.length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?",
					  QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM ta WHERE EntryID = '" + id + "'");
			on_cboMonths_editTextChanged(ui->cboMonths->currentText());
		}
	}
}

void TaMW::on_cboMonths_currentIndexChanged(const QString &arg1)
{
	on_cboMonths_editTextChanged(arg1);
}
