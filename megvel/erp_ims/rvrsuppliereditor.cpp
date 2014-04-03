#include "rvrsuppliereditor.h"
#include "ui_rvrsuppliereditor.h"
#include <QMessageBox>
#include "datapublics.h"
RvrSupplierEditor::RvrSupplierEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::RvrSupplierEditor)
{
	ui->setupUi(this);
	db = database;
	isAdding = true;
}

RvrSupplierEditor::~RvrSupplierEditor()
{
	delete ui;
}

void RvrSupplierEditor::Edit(QString supplierID)
{
	isAdding = false;
	currentID = supplierID;
	QSqlQuery qu = db.exec("SELECT * FROM ims.suppliers WHERE EntryID = '" + currentID + "'");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
	}
	qu.first();
	QSqlRecord rec = qu.record();
	ui->txtSupplierName->setText(rec.value("SupplierName").toString());
	ui->txtAddress->setText(rec.value("Address").toString());
	ui->txtContactEmail->setText(rec.value("ContactEmail").toString());
	ui->txtContactName->setText(rec.value("ContactName").toString());
	ui->txtCountry->setText(rec.value("Country").toString());
	ui->txtEmail->setText(rec.value("Email").toString());
	ui->txtFax->setText(rec.value("Fax").toString());
	ui->txtTel->setText(rec.value("Tel").toString());
	ui->txtTown->setText(rec.value("Town").toString());
	ui->txtWebsite->setText(rec.value("Website").toString());
}

void RvrSupplierEditor::AddNew()
{
	isAdding = true;
}

void RvrSupplierEditor::on_cmdSave_clicked()
{
	QString query = "SELECT NOW()";

	if (isAdding) {
		query = "INSERT INTO ims.suppliers (SupplierName, Address, "
				"ContactEmail, ContactName, Country, Email, Fax, Tel, Town, Website ) VALUES ('"
				+ ui->txtSupplierName->text() + "', '"
				+ ui->txtAddress->text() + "', '"
				+ ui->txtContactEmail->text()  + "', '"
				+ ui->txtContactName->text()  + "', '"
				+ ui->txtCountry->text()  + "', '"
				+ ui->txtEmail->text()  + "', '"
				+ ui->txtFax->text()  + "', '"
				+ ui->txtTel->text()  + "', '"
				+ ui->txtTown->text()  + "', '"
				+ ui->txtWebsite->text() + "')";
	} else {
		query = "UPDATE ims.suppliers SET "
				" SupplierName = '" + ui->txtSupplierName->text() + "', "
				" Address = '" + ui->txtAddress->text()  + "', "
				" ContactEmail = '" + ui->txtContactEmail->text()  + "', "
				" ContactName = '" + ui->txtContactName->text()  + "', "
				" Country = '" + ui->txtCountry->text()  + "', "
				" Email = '" + ui->txtEmail->text()  + "', "
				" Fax = '" + ui->txtFax->text()  + "', "
				" Tel = '" + ui->txtTel->text()  + "', "
				" Town = '" + ui->txtTown->text()  + "', "
				" Website = '" + ui->txtWebsite->text() + "' WHERE EntryID = '" + currentID + "'";
	}

	db.exec(query);
	if (db.lastError().isValid()) {
		QMessageBox::critical(this, "Error", db.lastError().text());
	} else {
		this->accept();
	}
}
