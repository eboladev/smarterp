#include "producteditor.h"
#include "ui_producteditor.h"

ProductEditor::ProductEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductEditor)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("closures");
    DataPublics::loadQueryToComboBox("SELECT * FROM customers", "CompanyName", db, ui->cboCustomer);
    DataPublics::loadQueryToComboBox("SELECT * FROM inks", "ink_name", db, ui->cboInk1);
    DataPublics::loadQueryToComboBox("SELECT * FROM inks", "ink_name", db, ui->cboInk2);

    DataPublics::loadQueryToComboBox("SELECT * FROM colors ORDER By color_name", "color_name", db, ui->cboColor);
    DataPublics::loadQueryToComboBox("SELECT * FROM bottle_names", "bottle_name", db, ui->cboBottleName);

    isAdding  = true;
}

ProductEditor::~ProductEditor()
{
    delete ui;
}

void ProductEditor::Edit(QString productID)
{
    isAdding  = false;
    currentID = productID;
    QSqlQuery qu = db.exec("SELECT * FROM products WHERE product_id = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }

    qu.first();
    ui->txtProductCode->setText(qu.record().value("product_code").toString());
    ui->txtProductName->setText(qu.record().value("product_name").toString());
    ui->spinPrice->setValue(qu.record().value("price_per_thousand").toDouble());
    ui->spinPricePerPiece->setValue(qu.record().value("price_per_piece").toDouble());
    ui->spinWt->setValue(qu.record().value("wt").toDouble());
    ui->cboFinishing->setEditText(qu.record().value("finishing").toString());
    ui->cboColor->setEditText(qu.record().value("color").toString());

    ui->txtProductionDesc->setText(qu.record().value("production_description").toString());
    ui->txtSalesDesc->setText(qu.record().value("quickbooks_description").toString());

    ui->chkPrinted->setChecked(qu.record().value("printed").toString() == "yes");

    if (qu.record().value("packing").toString() == "Both") {
        ui->radioCartonAndLiner->setChecked(true);
    } else {
        ui->radioLinerOnly->setChecked(true);
    }

    ui->spinPiecesPerPack->setValue(qu.record().value("caps_per_pack").toDouble());

    QString customerName = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + qu.record().value("customer_id").toString()
                                                   + "'", db, "CompanyName"
                                                   ).toString();
    for (int i = 0; i < ui->cboCustomer->count(); i++) {
        if (ui->cboCustomer->itemText(i) == customerName)
            ui->cboCustomer->setCurrentIndex(i);
    }

    QString ink1Id = qu.record().value("ink1").toString();
    QString ink2Id = qu.record().value("ink2").toString();
    QString colorId = qu.record().value("color").toString();

    DataPublics::setComboBoxTextBasedOnID("colors", "color_id", colorId, "color_name", ui->cboColor);

    if (ink1Id.length() > 0) {
        DataPublics::setComboBoxTextBasedOnID("inks", "ink_id", ink1Id, "ink_name", ui->cboInk1);
        DataPublics::setComboBoxTextBasedOnID("inks", "ink_id", ink2Id, "ink_name", ui->cboInk2);
    }

    ui->cboBottleType->clear();
    DataPublics::loadQueryToComboBox("SELECT * FROM bottle_types WHERE name_id = '" + qu.record().value("bottle_name").toString() + "'", "bottle_type", QSqlDatabase::database(), ui->cboBottleType);

    QString bottleType = DataPublics::getDbValue("SELECT bottle_type FROM bottle_types WHERE entry_id = '" + qu.record().value("bottle_type").toString() + "'", QSqlDatabase::database(), "bottle_type").toString();

    ui->cboBottleName->setCurrentIndex(ui->cboBottleName->findData(qu.record().value("bottle_name").toString(), Qt::UserRole));
    //ui->cboBottleType->setCurrentIndex(ui->cboBottleName->findData(qu.record().value("bottle_type").toString(), Qt::UserRole));
    ui->cboBottleType->setCurrentIndex(ui->cboBottleType->findText(bottleType));
    ui->spinBottlePrice->setValue(qu.record().value("bottle_price").toDouble());
    ui->chkBottles->setChecked(qu.record().value("has_bottles").toString() == "yes");

    ui->txtTotalPrice->setText(qu.record().value("total_price").toString());
}


void ProductEditor::StartNew(QString customerID)
{

    QString customerName = DataPublics::getDbValue("SELECT * FROM customers WHERE CustomerID = '" + customerID
                                                   + "'", db, "CompanyName"
                                                   ).toString();
    for (int i = 0; i < ui->cboCustomer->count(); i++) {
        if (ui->cboCustomer->itemText(i) == customerName)
            ui->cboCustomer->setCurrentIndex(i);
    }

    isAdding = true;
}

void ProductEditor::on_cmdSave_clicked()
{
    QString printed = "no";
    if (ui->chkPrinted->isChecked())
        printed = "yes";

    QString customerID =
            DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'"
                                    , db, "CustomerID"
                                    ).toString();

    QString qb_master_id =
            DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'"
                                    , db, "item_quickbooks_id"
                                    ).toString();

    if (isAdding) {
        QString tmpQuery = "INSERT INTO products (product_name, customer_id) VALUES ('"
                + ui->txtProductName->text() + "', '"
                + customerID + "')";
        QSqlQuery tmpQu = db.exec(tmpQuery);
        if (tmpQu.lastError().isValid()) {
            DataPublics::showWarning(tmpQu.lastError().text());
            return;
        }
        currentID = tmpQu.lastInsertId().toString();
        isAdding = false;
    }

    if (ui->txtProductCode->text().trimmed() == "")
        ui->txtProductCode->setText(currentID);


    QString has_bottles = "no";
    if (ui->chkBottles->isChecked())
        has_bottles = "yes";
    QString bottle_name = ui->cboBottleName->itemData(ui->cboBottleName->currentIndex(), Qt::UserRole).toString();
    QString bottle_type = ui->cboBottleType->itemData(ui->cboBottleType->currentIndex(), Qt::UserRole).toString();

    QString bottle_price = QString::number(ui->spinBottlePrice->value());

    QString packing = "Both";
    if (ui->radioLinerOnly->isChecked())
        packing = "Liner Only";

    QString ink1 = DataPublics::getDbValue("SELECT * FROM inks WHERE ink_name = '" + ui->cboInk1->currentText() + "'"
                                           , db, "ink_id"
                                           ).toString();
    QString ink2 = DataPublics::getDbValue("SELECT * FROM inks WHERE ink_name = '" + ui->cboInk2->currentText() + "'"
                                           , db, "ink_id"
                                           ).toString();

    QString colorId = DataPublics::getDbValue("SELECT * FROM colors WHERE color_name = '" + ui->cboColor->currentText() + "'"
                                              , db, "color_id"
                                              ).toString();

    QString str_qu = "UPDATE products SET "
            " product_code = '" + ui->txtProductCode->text()
            + "', product_name = '" + ui->txtProductName->text()
            + "', customer_id = '" + customerID
            + "', printed = '" + printed
            + "', ink1 = '" + ink1
            + "', ink2 = '" + ink2
            + "', finishing = '" + ui->cboFinishing->currentText()
            + "', has_bottles = '" + has_bottles
            + "', bottle_name = '" + bottle_name
            + "', bottle_type = '" + bottle_type
            + "', bottle_price = '" + bottle_price
            + "', quickbooks_master_id = '" + qb_master_id
            + "', packing = '" + packing
            + "', quickbooks_updated = 'No',"
            + "total_price = '" + ui->txtTotalPrice->text()
            + "', production_description = '" + ui->txtProductionDesc->text()
            + "', quickbooks_description = '" + ui->txtSalesDesc->text()
            + "', color = '" + colorId
            +"', wt = '" + QString::number(ui->spinWt->value())
            + "', price_per_thousand = '" + QString::number(ui->spinPrice->value())
            + "', price_per_piece = '" + QString::number(ui->spinPricePerPiece->value())
            + "', caps_per_pack = '" + QString::number(ui->spinPiecesPerPack->value())
            + "' WHERE product_id = '" + currentID + "'";
    qDebug() << str_qu;
    QSqlQuery qu = db.exec(str_qu);
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    } else {
        DataPublics::showInformation("Product Saved");
        emit changed();
    }
}

void ProductEditor::on_spinPricePerPiece_editingFinished()
{
    ui->spinPrice->setValue(ui->spinPricePerPiece->value() * 1000);
    recalculatePrices();
}

void ProductEditor::on_spinPrice_editingFinished()
{
    if (ui->spinPrice->value()) {
        ui->spinPricePerPiece->setValue(ui->spinPrice->value() / 1000);
    } else {
        ui->spinPricePerPiece->setValue(0);
    }
    recalculatePrices();
}

void ProductEditor::on_cboBottleName_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString bottleName = ui->cboBottleName->currentText();
    QString nameID = DataPublics::getDbValue("SELECT * FROM bottle_names WHERE bottle_name = '" + bottleName + "'", QSqlDatabase::database(), "entry_id").toString();

    ui->cboBottleType->clear();
    DataPublics::loadQueryToComboBox("SELECT * FROM bottle_types WHERE name_id = '" + nameID + "'"
                                     , "bottle_type", QSqlDatabase::database(), ui->cboBottleType);

    QString bottle_id = DataPublics::getDbValue("SELECT bottle_type FROM products WHERE product_id = '" + currentID + "'", QSqlDatabase::database(), "bottle_type").toString();

    if (bottle_id != "-1") {
        ui->cboBottleType->setCurrentIndex(ui->cboBottleType->findData(bottle_id));
    }
}

void ProductEditor::recalculatePrices()
{
    double total_price = 0;

    total_price = ui->spinPricePerPiece->value();
    if (ui->chkBottles->isChecked())
        total_price = total_price + ui->spinBottlePrice->value();

    ui->txtTotalPrice->setText(QString::number(total_price));
}

void ProductEditor::on_spinBottlePrice_editingFinished()
{
    recalculatePrices();
}

void ProductEditor::on_chkBottles_toggled(bool checked)
{
    Q_UNUSED(checked);
    recalculatePrices();
}

void ProductEditor::on_cmdDelete_clicked()
{
    if (currentID.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this product?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("UPDATE products SET deleted = 'Yes' WHERE product_id = '" + currentID + "'");
            if (db.lastError().isValid()) {
                QMessageBox::critical(this, "Error", db.lastError().text());
                return;
            } else {
                emit changed();
                this->accept();
            }
        }
    }
}
