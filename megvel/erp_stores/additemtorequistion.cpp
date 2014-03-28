#include "additemtorequistion.h"
#include "ui_additemtorequistion.h"
#include "datapublics.h"

AddItemToRequistion::AddItemToRequistion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemToRequistion)
{
    ui->setupUi(this);
    db = QSqlDatabase::database();
    DataPublics::loadQueryToComboBox("SELECT * FROM inventory", "ItemName", db, ui->cboItem);
}

AddItemToRequistion::~AddItemToRequistion()
{
    delete ui;
}

void AddItemToRequistion::on_pushButton_clicked()
{
    itemName = ui->cboItem->currentText();
    qty = ui->spinQty->value();
    unitPrice = ui->spinUnitPrice->value();
    vat = ui->spinVATRate->value();
    this->accept();
}

void AddItemToRequistion::on_pushButton_2_clicked()
{
    this->reject();
}

void AddItemToRequistion::on_cboItem_currentIndexChanged(const QString &arg1)
{
    QString unitPrice = DataPublics::getDbValue("SELECT UnitPrice FROM inventory WHERE ItemName = '" + arg1 + "'", db, "UnitPrice").toString();
    ui->spinUnitPrice->setValue(unitPrice.toDouble());
}
