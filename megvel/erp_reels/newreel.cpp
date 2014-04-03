#include "newreel.h"
#include "ui_newreel.h"
#include "datapublics.h"
NewReel::NewReel(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::NewReel)
{
	ui->setupUi(this);
	ui->dtpAsOf->setDate(QDate::currentDate());
	db = database;
}

NewReel::~NewReel()
{
	delete ui;
}

void NewReel::on_cmdSave_clicked()
{
	if (ui->txtSupplierReelNumber->text().trimmed() == "" || ui->txtReelNumber->text().trimmed() == "") {
		DataPublics::showWarning("Enter the reel number and supplier reel number.");
		return;
	}

	QString query = "INSERT INTO `reels` (ReelNumber, SupplierReelNumber, Supplier, StoreID, Size, GSM"
			", Type, Weight) VALUES ('"
			+ ui->txtReelNumber->text() + "', '"
			+ ui->txtSupplierReelNumber->text() + "', '"
			+ ui->cboSupplier->currentText() + "', '1', '"
			+ ui->cboSize->currentText()  + "', '"
			+ ui->cboGSM->currentText()  + "', '"
			+ ui->cboType->currentText()  + "', '"
			+ ui->txtOpeningWeight->text()  + "')";


	QSqlQuery qu = db.exec(query);

	if (qu.lastError().isValid()) {
		DataPublics::showWarning("A database error has occured.\n\n" + qu.lastError().text());
		return;
	} else {
		db.exec("UPDATE reels SET LastModified = Current_Date() WHERE ReelID = '" + qu.lastInsertId().toString() + "'");
		this->accept();
	}
}
