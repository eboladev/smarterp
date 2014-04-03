#include "newphonecall.h"
#include "ui_newphonecall.h"

#include "publics.h"
#include "transactionview.h"
#include "appointment.h"
NewPhoneCall::NewPhoneCall(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewPhoneCall)
{
	ui->setupUi(this);
	Publics::loadDbToComboBox(Publics::getDatabase(), ui->cboCustomer, "SELECT * FROM customers", "CompanyName");
	ui->dtpDate->setDate(QDate::currentDate());
	ui->dtpTime->setTime(QTime::currentTime());
}

NewPhoneCall::~NewPhoneCall()
{
	delete ui;
}

void NewPhoneCall::on_cmdSave_clicked()
{
	QString customerID = Publics::getDbValue(Publics::getDatabase(), "SELECT CustomerID FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'", "CustomerID");
	if (customerID.length() > 0) {
		QDate startDate = ui->dtpDate->date();
		QTime startTime = ui->dtpTime->time();
		QTime endTime = ui->dtpTime->time().addSecs(ui->spinDuration->value() * 60);
		QSqlQuery qu = Publics::getDatabase().exec("INSERT INTO appointments (AppointmentType, CustomerID, "
							   " StartDate, StartTime, EndDate, EndTime, Location, Subject, Description) VALUES ('1', '"
							   + customerID + "', '"
							   + startDate.toString("yyyy-MM-dd")  + "', '"
							   + startTime.toString("HH:mm:ss") + "', '"
							   + startDate.toString("yyyy-MM-dd")  + "', '"
							   + endTime.toString("HH:mm:ss") + "', '"
							   + "Office"  + "', '"
							   + ui->txtSubject->text()  + "', '"
							   + ui->txtNotes->toPlainText()  + "'"
							   + ")");
		if (qu.lastError().isValid()) {
			Publics::showError(qu.lastError().text());
		} else {
			this->accept();
		}
	} else {
		Publics::showError("Please select a customer.");
	}

}
