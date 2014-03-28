#include "ims_producteditor.h"
#include "ui_ims_producteditor.h"

IMS_ProductEditor::IMS_ProductEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::IMS_ProductEditor)
{
    ui->setupUi(this);
    db = database;
}

IMS_ProductEditor::~IMS_ProductEditor()
{
    delete ui;
}

void IMS_ProductEditor::AddNew(QString fileID)
{
    currentFileID = fileID;
    isAdding = true;
}

void IMS_ProductEditor::Edit(QString productID)
{
    currentProductId = productID;
    isAdding = false;
    if (productID.length() > 0) {
        QSqlQuery qu = db.exec("SELECT * FROM ims.products WHERE EntryID = '" + productID + "'");
        if (!qu.lastError().isValid()) {
            while (qu.next()) {
                QSqlRecord rec = qu.record();
                ui->txtLPO_ProductName->setText(rec.value("ProductName").toString());
                ui->txtLPO_Description->setText(rec.value("Description").toString());
                ui->txtLPO_Qty->setText(rec.value("Qty").toString());
                ui->cboLPO_UnitOfQty->setEditText(rec.value("UnitOfQty").toString());
                ui->txtLPO_UnitPrice->setText(rec.value("UnitPrice").toString());
                ui->txtLPO_HSCode->setText(rec.value("ProductHS").toString());
                ui->txtLPO_FOBValue->setText(rec.value("ProductFOB").toString());
                ui->txtLPO_CountryOfOrigin->setText(rec.value("Origin").toString());

            }
        } else {
            qDebug() << qu.lastError().text();
        }
    } else {
        qDebug() << "Invalid Product Code";
    }
}


void IMS_ProductEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";
    if (isAdding) {
        query = "INSERT INTO ims.products (FileID, ProductName, Description, Qty, UnitOfQty, UnitPrice, ProductHS, ProductFOB,"
                "Origin) VALUES ('"
                + currentFileID + "', '"
                + ui->txtLPO_ProductName->text() + "', '"
                + ui->txtLPO_Description->text() + "', '"
                + ui->txtLPO_Qty->text() + "', '"
                + ui->cboLPO_UnitOfQty->currentText() + "', '"
                + ui->txtLPO_UnitPrice->text() + "', '"
                + ui->txtLPO_HSCode->text()  + "', '"
                + ui->txtLPO_FOBValue->text()  + "', '"
                + ui->txtLPO_CountryOfOrigin->text() + "')";
    } else {
        query = "UPDATE ims.products SET "
                " ProductName = '" + ui->txtLPO_ProductName->text() + "', "
                " Description = '" + ui->txtLPO_Description->text()  + "', "
                " Qty = '" + ui->txtLPO_Qty->text()  + "', "
                " UnitOfQty = '" + ui->cboLPO_UnitOfQty->currentText()  + "', "
                " ProductHS = '" + ui->txtLPO_HSCode->text()  + "', "
                " ProductFOB = '" + ui->txtLPO_FOBValue->text()  + "', "
                " Origin = '" + ui->txtLPO_CountryOfOrigin->text() + "' WHERE EntryID = '" + currentProductId + "'";
    }

    db.exec(query);

    if (db.lastError().isValid()) {
        DataPublics::showWarning(db.lastError().text());
    } else {
        this->accept();
    }
}
