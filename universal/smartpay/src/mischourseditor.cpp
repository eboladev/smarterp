#include "mischourseditor.h"
#include "ui_mischourseditor.h"
#include "datapublics.h"

MiscHoursEditor::MiscHoursEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::MiscHoursEditor)
{
	ui->setupUi(this);
	db = database;
	isAdding = false;

	DataPublics::loadQueryToComboBox("SELECT * FROM vw_employeenames_ex", "Name", db, ui->cboEmployee);
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex", "month", db, ui->cboPayrollMonth);

	ui->dtpDateIssued->setDate(QDate::currentDate());
}

MiscHoursEditor::~MiscHoursEditor()
{
	delete ui;
}


void MiscHoursEditor::Edit(QString miscID)
{
	currentID = miscID;
	isAdding = false;
	QSqlQuery qu = db.exec("SELECT * FROM misc_hours WHERE MiscID = '" + currentID + "'");
	if (qu.lastError().isValid()) {

	} else {
		qu.first();
		ui->txtComment->setText(qu.record().value("Comment").toString());
		ui->cboType->setEditText(qu.record().value("Type").toString());
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

		ui->spinAmount->setValue(qu.record().value("Hours").toString().toDouble());
		ui->dtpDateIssued->setDate(qu.record().value("DateIssued").toDate());
	}
}

void MiscHoursEditor::on_cmdSave_clicked()
{
	QString query = "";
	QString employeeID = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE Name  = '" + ui->cboEmployee->currentText() + "'", db, "employeeID").toString();
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE month = '" + ui->cboPayrollMonth->currentText() + "'", db, "MonthID").toString();

	if (isAdding) {
		query = "INSERT INTO misc_hours (MonthID, EmployeeID, DateIssued, Hours, Type, Comment) VALUES ('" +
				monthID + "', '" + employeeID + "', '"
				+ ui->dtpDateIssued->date().toString("yyyy-MM-dd") + "', '"
				+ QString::number(ui->spinAmount->value()) + "', '"
				+ ui->cboType->currentText() + "', '"
				+ ui->txtComment->toPlainText() + "')";
	} else {
		query = "UPDATE misc_hours SET "
				" MonthID = '" + monthID + "', "
				" EmployeeID = '" + employeeID  + "', "
				" DateIssued = '" + ui->dtpDateIssued->date().toString("yyyy-MM-dd") + "', "
				" Hours = '" + QString::number(ui->spinAmount->value())  + "', "
				" Type = '" + ui->cboType->currentText()   + "', "
				" Comment = '" + ui->txtComment->toPlainText() + "' WHERE MiscID = '" + currentID + "'";
	}

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		QMessageBox::warning(this, "Error", qu.lastError().text());
	} else {
		this->accept();
	}
}


void MiscHoursEditor::AddNew(QString employeeID, QString type)
{
	isAdding = true;
	QString employeeName = DataPublics::getDbValue("SELECT * FROM vw_employeenames_ex WHERE employeeID  = '" + employeeID + "'", db, "Name").toString();
	ui->cboType->setEditText(type);
	for (int i = 0; i < ui->cboEmployee->count(); i++) {
		if (ui->cboEmployee->itemText(i) == employeeName) {
			ui->cboEmployee->setCurrentIndex(i);
		}
	}
}
