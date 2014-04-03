#include "finishing_dataentry.h"
#include "ui_finishing_dataentry.h"
#include "datapublics.h"
Finishing_DataEntry::Finishing_DataEntry(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::Finishing_DataEntry)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDate->setDate(QDate::currentDate());
	isAdding  = true;
}

Finishing_DataEntry::~Finishing_DataEntry()
{
	delete ui;
}

void Finishing_DataEntry::AddNew(QString section, QDate date)
{
	ui->cboSection->setEditText(section);
	ui->dtpDate->setDate(date);
	isAdding = true;
}

void Finishing_DataEntry::Edit(QString finishingID)
{
	isAdding  = false;
	currentID = finishingID;

	QSqlQuery qu = db.exec("SELECT * FROM finishingdataentry WHERE EntryID = '" + currentID + "'");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	} else {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->dtpDate->setDate(rec.value("Date").toDate());
		ui->cboShift->setEditText(rec.value("Shift").toString());
		ui->txtOrderNo->setText(rec.value("OCNo").toString());
		ui->txtProduced->setText(rec.value("Produced").toString());
		ui->txtWasted->setText(rec.value("Wasted").toString());
		ui->txtDispatch->setText(rec.value("Dispatch").toString());

		ui->spinStart->setTime(QTime::fromString(rec.value("StartTime").toString(), "hh:mm AP"));
		ui->spinStop->setTime(QTime::fromString(rec.value("StopTime").toString(), "hh:mm AP"));

		ui->cboSection->setEditText(rec.value("Section").toString());

		updateOrderDetails();
	}
}

void Finishing_DataEntry::on_cmdSave_clicked()
{
	QString query = "";
	QString section = ui->cboSection->currentText();

	if (section == "Gluing - H")
		section = "Gluing";

	if (isAdding) {
		query = "INSERT INTO finishingdataentry (Date, Shift, OCNo, StartTime, Produced, Wasted, Dispatch, StopTime, Section) VALUES ('" +
				ui->dtpDate->date().toString("yyyy-MM-dd") + "', '" +
				ui->cboShift->currentText() + "', '" +
				ui->txtOrderNo->text()  + "', '" +
				ui->spinStart->time().toString("hh:mm AP") + "', '" +
				ui->txtProduced->text() + "', '" +
				ui->txtWasted->text() + "', '" +
				ui->txtDispatch->text() + "', '" +
				ui->spinStop->time().toString("hh:mm AP") + "', '" +
				section + "')";
	} else {
		query = "UPDATE finishingdataentry SET "
				" Date = '" + ui->dtpDate->date().toString("yyyy-MM-dd") + "', "
				" Shift = '" + ui->cboShift->currentText() + "', "
				" OCNo = '" + ui->txtOrderNo->text() + "', "
				" StartTime = '" + ui->spinStart->time().toString("hh:mm AP") + "', "
				" StopTime = '" + ui->spinStop->time().toString("hh:mm AP") + "', "
				" Produced = '" + ui->txtProduced->text() + "', "
				" Wasted = '" + ui->txtWasted->text() + "', "
				" Dispatch = '" + ui->txtDispatch->text() + "', "
				" Section = '" + section + "' WHERE EntryID = '" + currentID + "'";
	}

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}

	this->accept();
}

void Finishing_DataEntry::updateOrderDetails()
{
	QString client = DataPublics::getDbValue("SELECT * FROM newreport WHERE TicketNo = '" + ui->txtOrderNo->text() + "'", db, "Client").toString();
	QString product = DataPublics::getDbValue("SELECT * FROM newreport WHERE TicketNo = '" + ui->txtOrderNo->text() + "'", db, "Product").toString();
	QString order_qty = DataPublics::getDbValue("SELECT * FROM newreport WHERE TicketNo = '" + ui->txtOrderNo->text() + "'", db, "Qty").toString();

	QString preview = "<b>Client: </b>" + client + "<br/>" +
			"<b>Product: </b>" + product + "<br/>" +
			"<b>Order Qty: </b>" + order_qty + "<br/>";

	ui->txtOrderDetails->setHtml(preview);
}

void Finishing_DataEntry::on_txtOrderNo_editingFinished()
{
	updateOrderDetails();
}
