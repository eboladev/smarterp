#include "wastedataentry.h"
#include "ui_wastedataentry.h"

WasteDataEntry::WasteDataEntry(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::WasteDataEntry)
{
	ui->setupUi(this);
	db =  database;
	ui->dtpDate->setDate(QDate::currentDate());
	isAdding = true;
}

WasteDataEntry::~WasteDataEntry()
{
	delete ui;
}

void WasteDataEntry::AddNew()
{
	isAdding = true;
	ui->cmdDelete->setEnabled(false);
}

void WasteDataEntry::edit()
{
	QSqlQuery qu = db.exec("SELECT * FROM corrugator_waste WHERE EntryID = '" + currentID + "'");
	if (qu.lastError().isValid()) {
		QMessageBox::critical(this, "Error", qu.lastError().text());
		return;
	} else {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->dtpDate->setDate(rec.value("Date").toDate());
		ui->txtDryEndComment->setPlainText(rec.value("DryEndComment").toString());
		ui->txtWetEndComment->setPlainText(rec.value("WetEndComment").toString());
		ui->spinCorrugatorTime->setValue(rec.value("CorrugatorMinutes").toDouble());
		ui->spinDryEnd->setValue(rec.value("DryEnd").toDouble());
		ui->spinPaperInput->setValue(rec.value("PaperInput").toDouble());
		ui->spinProducedOrders->setValue(rec.value("ProducedOrders").toDouble());
		ui->spinWetEnd->setValue(rec.value("WetEnd").toDouble());
	}
}

void WasteDataEntry::on_cmdSave_clicked()
{
	QString query = "";
	if (isAdding) {
		query  = "INSERT INTO corrugator_waste (Date, WetEnd, WetEndComment, DryEnd, DryEndComment, PaperInput, ProducedOrders, CurrugatorMinutes) VALUES ('"
				+ ui->dtpDate->date().toString("yyyy-MM-dd") + "', '"
				+ QString::number(ui->spinWetEnd->value())  + "', '"
				+ ui->txtWetEndComment->toPlainText() + "', '"
				+ QString::number(ui->spinDryEnd->value())  + "', '"
				+ ui->txtDryEndComment->toPlainText() + "', '"
				+ QString::number(ui->spinPaperInput->value())  + "', '"
				+ QString::number(ui->spinProducedOrders->value())  + "', '"
				+ QString::number(ui->spinCorrugatorTime->value()) + "')";
	} else {
		query  = "UPDATE corrugator_waste SET Date = '"
				+ ui->dtpDate->date().toString("yyyy-MM-dd") + "', WetEnd = '"
				+ QString::number(ui->spinWetEnd->value())  + "', WetEndComment = '"
				+ ui->txtWetEndComment->toPlainText() + "', DryEnd =  '"
				+ QString::number(ui->spinDryEnd->value())  + "', PaperInput =  '"
				+ QString::number(ui->spinPaperInput->value())  + "', ProducedOrders =  '"
				+ QString::number(ui->spinProducedOrders->value())  + "', DryEndComment =  '"
				+ ui->txtDryEndComment->toPlainText() + "', CurrugatorMinutes = '"
				+ QString::number(ui->spinCorrugatorTime->value()) + "' WHERE EntryID = '" + currentID + "'";
	}

	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		QMessageBox::critical(this, "Error", qu.lastError().text());
		return;
	} else {
		this->accept();
	}
}
