#include "saccopaymenteditor.h"
#include "ui_saccopaymenteditor.h"
#include "datapublics.h"
SaccoPaymentEditor::SaccoPaymentEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::SaccoPaymentEditor)
{
	ui->setupUi(this);
	db = database;
	isAdding = false;

	DataPublics::loadQueryToComboBox("SELECT * FROM vw_employeenames_ex", "Name", db, ui->cboEmployee);
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex", "month", db, ui->cboPayrollMonth);

	ui->dtpDateIssued->setDate(QDate::currentDate());
}

SaccoPaymentEditor::~SaccoPaymentEditor()
{
	delete ui;
}

void SaccoPaymentEditor::Edit(QString paymentID)
{
	currentID = paymentID;
	isAdding = false;
	QSqlQuery qu = db.exec("SELECT * FROM sacco_payments WHERE PaymentID = '" + currentID + "'");
	if (qu.lastError().isValid()) {

	} else {
		qu.first();
		ui->txtComment->setText(qu.record().value("Comment").toString());
		QString employeeID = qu.record().value("EmployeeID").toString();
		QString monthID = qu.record().value("MonthID").toString();

		QString employeeName = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE employeeID  = '" + employeeID + "'", db, "Name").toString();
		QString monthName = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE MonthID = '" + monthID + "'", db, "month").toString();

		for (int i = 0; i < ui->cboEmployee->count(); i++) {
			if (ui->cboEmployee->itemText(i) == employeeName) {
				ui->cboEmployee->setCurrentIndex(i);

			}
		}
		for (int i = 0; i < ui->cboPayrollMonth->count(); i++) {
			if (ui->cboPayrollMonth->itemText(i) == monthName) {
				ui->cboPayrollMonth->setCurrentIndex(i);

			}
		}

		ui->spinAmount->setValue(qu.record().value("Amount").toString().toDouble());
		ui->dtpDateIssued->setDate(qu.record().value("DateIssued").toDate());
	}
}

void SaccoPaymentEditor::AddNew(QString employeeID)
{
	isAdding = true;
	QString employeeName = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE employeeID  = '" + employeeID + "'", db, "Name").toString();

	for (int i = 0; i < ui->cboEmployee->count(); i++) {
		if (ui->cboEmployee->itemText(i) == employeeName) {
			ui->cboEmployee->setCurrentIndex(i);
		}
	}
}

void SaccoPaymentEditor::on_cmdSave_clicked()
{
	QString query = "";
	QString employeeID = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE Name  = '" + ui->cboEmployee->currentText() + "'", db, "employeeID").toString();
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE month = '" + ui->cboPayrollMonth->currentText() + "'", db, "MonthID").toString();

	if (isAdding) {
		query = "INSERT INTO sacco_payments (MonthID, EmployeeID, DateIssued, Amount, Comment) VALUES ('" +
				monthID + "', '" + employeeID + "', '"
				+ ui->dtpDateIssued->date().toString("yyyy-MM-dd") + "', '"
				+ QString::number(ui->spinAmount->value()) + "', '"
				+ ui->txtComment->toPlainText() + "')";
	} else {
		query = "UPDATE sacco_payments SET "
				" MonthID = '" + monthID + "', "
				" EmployeeID = '" + employeeID  + "', "
				" DateIssued = '" + ui->dtpDateIssued->date().toString("yyyy-MM-dd") + "', "
				" Amount = '" + QString::number(ui->spinAmount->value())  + "', "
				" Comment = '" + ui->txtComment->toPlainText() + "' WHERE PaymentID = '" + currentID + "'";
	}

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		QMessageBox::warning(this, "Error", qu.lastError().text());
	} else {
		this->accept();
	}
}
