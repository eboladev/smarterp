#include "newrequisition.h"
#include "ui_newrequisition.h"
#include "datapublics.h"
NewRequisition::NewRequisition(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NewRequisition)
{
	ui->setupUi(this);
	QSqlDatabase db = QSqlDatabase::database();
	DataPublics::loadQueryToComboBox("SELECT * FROM inventory", "ItemName", db, ui->cboItem);
	DataPublics::loadQueryToComboBox("SELECT * FROM suppliers", "SupplierName", db, ui->cboSupplier);
	ui->dtpDateNeeded->setDate(QDate::currentDate().addDays(3));
	ui->dtpRqnDate->setDate(QDate::currentDate());
}

NewRequisition::~NewRequisition()
{
	delete ui;
}

void NewRequisition::on_cmdSave_clicked()
{
	QSqlDatabase db = QSqlDatabase::database();
	QString itemID = DataPublics::getDbValue("SELECT * FROM inventory WHERE ItemName = '" + ui->cboItem->currentText() + "'", db, "ItemID").toString();
	QString supplierID = DataPublics::getDbValue("SELECT * FROM suppliers WHERE SupplierName = '" + ui->cboSupplier->currentText() + "'", db, "SupplierID").toString();

	QSqlQuery qu = db.exec("INSERT INTO qt_requisition (ItemID, SupplierID, ReqnDate, RequiredDate, RequestedBy, Department, Qty) VALUES ('"
			       + itemID + "', '"
			       + supplierID + "', '"
			       + ui->dtpRqnDate->date().toString("yyyy-MM-dd") + "', '"
			       + ui->dtpDateNeeded->date().toString("yyyy-MM-dd") + "', '"
			       + ui->txtRqnBy->text() + "', '"
			       + ui->txtDept->text() + "', '"
			       + ui->txtQty->text() + "')");
	if (!qu.lastError().isValid()) {
		this->accept();
	} else {
		DataPublics::showWarning(qu.lastError().text());
	}
}
