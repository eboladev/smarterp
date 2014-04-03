#include "newdispatchdialog.h"
#include "ui_newdispatchdialog.h"
#include "datapublics.h"
NewDispatchDialog::NewDispatchDialog(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::NewDispatchDialog)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDispatchDate->setDate(QDate::currentDate());
}

NewDispatchDialog::~NewDispatchDialog()
{
	delete ui;
}

void NewDispatchDialog::on_txtOcNo_textChanged(const QString &arg1)
{
	QSqlQuery qu = db.exec("SELECT Client, Product, Qty, Dispatched FROM newreport WHERE TicketNo = '" + arg1 + "'");
	if (qu.size() < 1 || qu.lastError().isValid()) {
		ui->txtCustomer->setText("");
		ui->txtProduct->setText("");
		ui->txtProducedQty->setText("0");
		ui->txtQtyDispatched->setText("0");
		ui->txtOrderQty->setText("0");
		ui->txtRemainingAmount->setText("0");
	} else {
		qu.first();
		ui->txtCustomer->setText(qu.record().value("Client").toString());
		ui->txtProduct->setText(qu.record().value("Product").toString());
		ui->dispatched->setText(qu.record().value("Dispatched").toString());
		ui->txtOrderQty->setText(qu.record().value("Qty").toString());

		double produced = DataPublics::getDbValue("SELECT SUM(Produced) AS 'Tot' FROM finishingdataentry WHERE ocNo = '" + arg1 + "' AND Deleted = 'No'", db, "Tot").toDouble();
		ui->txtProducedQty->setText(QString::number(produced));

		if (ui->txtProducedQty->text().toDouble() < 1)
			ui->txtProducedQty->setText("0");

		double larger = ui->txtOrderQty->text().toDouble();
		if (ui->txtProducedQty->text().toDouble() > larger) {
			larger = ui->txtProducedQty->text().toDouble();
		}

		ui->txtRemainingAmount->setText(QString::number(larger - ui->dispatched->text().toDouble()));
	}


}

void NewDispatchDialog::on_cmdOK_clicked()
{
	QString query = "INSERT INTO dispatch (userID, date, JobTicketNumber, InvoiceNumber, "
			"QtyDispatched, RemainingQty, VehicleNo, TripNo, Comments) VALUES ('" +
			DataPublics::getCurrentUserID() + "', '"
			+ QDate::currentDate().toString("yyyy-MM-dd") + "', '"
			+ ui->txtOcNo->text() + "', '"
			+ ui->txtInvoiceNo->text() + "', '"
			+ ui->txtQtyDispatched->text()  + "', '"
			+ QString::number(ui->txtRemainingAmount->text().toDouble() - ui->txtQtyDispatched->text().toDouble()) + "', '"
			+ ui->txtVehicleNo->text()+ "', '"
			+ ui->txtTripNo->text()+ "', '"
			+ ui->txtComment->toPlainText() + "')";
	db.exec(query);
	if (db.lastError().isValid()) {
		DataPublics::showWarning(db.lastError().text());
		return;
	}

	DataPublics::logAuditTrail("Dispatch", "Dispatch Entered: Oc No: " + ui->txtOcNo->text(), db);
	db.exec("UPDATE newreport SET Dispatched = '" + QString::number(ui->txtQtyDispatched->text().toDouble() - ui->dispatched->text().toDouble()) + "' WHERE TicketNo = '" + ui->txtOcNo->text() + "'");

	DataPublics::showInformation("Dispatch Saved.");
	this->accept();
}
