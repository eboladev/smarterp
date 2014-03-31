#include "customereditor.h"
#include "ui_customereditor.h"
#include "datapublics.h"
CustomerEditor::CustomerEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::CustomerEditor)
{
    ui->setupUi(this);
    isAdding = true;
    db = database;

    DataPublics::loadQueryToComboBox("SELECT * FROM salesreps", "FullName", db, ui->SalesRep);
    DataPublics::loadQueryToComboBox("SELECT * FROM salesreps", "FullName", db, ui->SecondarySalesRep);
}

CustomerEditor::~CustomerEditor()
{
    delete ui;
}

void CustomerEditor::edit(QString customerID)
{
    isAdding = false;
    currentID = customerID;
    QSqlQuery qu = db.exec("SELECT * FROM customers WHERE CustomerID = '" + currentID + "'");
    if (!qu.lastError().isValid()) {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->AccountNumber->setText(rec.value("AccountNumber").toString());
        ui->Adress->setText(rec.value("Address").toString());
        ui->CompanyName->setText(rec.value("CompanyName").toString());
        ui->Country->setText(rec.value("Country").toString());
        ui->Currency->setEditText(rec.value("Currency").toString());
        ui->Email->setText(rec.value("Email").toString());
        ui->Fax->setText(rec.value("Fax").toString());
        ui->Mobile->setText(rec.value("Mobile").toString());
        ui->Postcode->setText(rec.value("PostCode").toString());
        ui->Tel->setText(rec.value("Telephone").toString());
        ui->Town->setText(rec.value("Town").toString());

        ui->cboDefaultVAT->setEditText(rec.value("VAT").toString());

        ui->SalesContactEmail->setText(rec.value("ContactEmail").toString());
        ui->SalesContactMobile->setText(rec.value("ContactMobile").toString());
        ui->SalesContactName->setText(rec.value("ContactName").toString());
        ui->SalesContactPhone->setText(rec.value("ContactPhone").toString());
        ui->SalesContactTitle->setText(rec.value("ContactTitle").toString());

        ui->SalesContactEmail_2->setText(rec.value("FinanceContactEmail").toString());
        ui->SalesContactMobile_2->setText(rec.value("FinanceContactMobile").toString());
        ui->SalesContactName_2->setText(rec.value("FinanceContactName").toString());
        ui->SalesContactPhone_2->setText(rec.value("FinanceContactPhone").toString());
        ui->SalesContactTitle_2->setText(rec.value("FinanceContactTitle").toString());

        ui->CreditLimit->setText(rec.value("CreditLimit").toString());
        ui->StatementsEmail->setText(rec.value("StatementEmail").toString());
        ui->MinimumRP->setText(rec.value("MinimumRP").toString());

         ui->SalesRep->setEditText(DataPublics::getDbValue("SELECT * FROM salesreps WHERE SalesRepID = '" + rec.value("SalesRep").toString() + "'", db, "FullName").toString());
         ui->SecondarySalesRep->setEditText(rec.value("Second").toString());

    } else {
        DataPublics::showWarning("Database Error " + qu.lastError().text());
    }
}

void CustomerEditor::on_SaveButton_clicked()
{
    QString saveQuery = "SELECT NOW()";
    if (isAdding) {
        QSqlQuery saveQu1 = db.exec("INSERT INTO customers (CompanyName) VALUES ('" + ui->CompanyName->text() + "')");
        if (saveQu1.lastError().isValid()) {
            DataPublics::showWarning(saveQu1.lastError().text());
            return;
        }

        currentID = saveQu1.lastInsertId().toString();
        isAdding = false;
        on_SaveButton_clicked();
    } else {
        saveQuery = "UPDATE customers SET ";
        saveQuery.append(tr("\nAccountNumber = '%1', Address = '%2', CompanyName = '%3', Country = '%4', Currency = '%5', Email = '%6' ")
                         .arg(ui->AccountNumber->text(),
                              ui->Adress->text(),
                              ui->CompanyName->text(),
                              ui->Country->text(),
                              ui->Currency->currentText(),
                              ui->Email->text()));

        saveQuery.append( tr("\n,Fax = '%1', Mobile = '%2', Postcode = '%3', Telephone = '%4', Town = '%5' ")
                          .arg(ui->Fax->text(),
                               ui->Mobile->text(),
                               ui->Postcode->text(),
                               ui->Tel->text(),
                               ui->Town->text()));


        saveQuery.append(
                    tr("\n,ContactEmail = '%1', ContactMobile = '%2', ContactName = '%3', ContactPhone = '%4', ContactTitle = '%5' "
                       ).arg(
                        ui->SalesContactEmail->text(),
                        ui->SalesContactMobile->text(),
                        ui->SalesContactName->text(),
                        ui->SalesContactPhone->text(),
                        ui->SalesContactTitle->text()
                        ));

        saveQuery.append(
                    tr("\n,FinanceContactEmail = '%1', FinanceContactMobile = '%2', FinanceContactName = '%3'"
                       ", FinanceContactPhone = '%4', FinanceContactTitle = '%5' ")
                    .arg(
                        ui->SalesContactEmail_2->text(),
                        ui->SalesContactMobile_2->text(),
                        ui->SalesContactName_2->text(),
                        ui->SalesContactPhone_2->text(),
                        ui->SalesContactTitle_2->text()
                        )
                    );

        saveQuery.append(tr("\n,VAT = '%1' ").arg(ui->cboDefaultVAT->currentText()));

        saveQuery.append(
                    tr(",CreditLimit = '%3', StatementEmail = '%2', MinimumRP = '%3' ")
                    .arg(
                        ui->CreditLimit->text(),
                        ui->StatementsEmail->text(),
                        ui->MinimumRP->text()
                        ));

        QString salesRepID = DataPublics::getDbValue("SELECT * FROM salesreps WHERE FullName = '" + ui->SalesRep->currentText() + "'", db, "SalesRepID").toString();

        saveQuery.append(tr(",SalesRep = '%1', Second = '%2' ")
                         .arg(salesRepID, ui->SecondarySalesRep->currentText()
                             )
                         );

        saveQuery.append(" WHERE CustomerID = '" + currentID + "'");

    }

    //QMessageBox::information(this, "", saveQuery);

    if (!db.exec(saveQuery).lastError().isValid()) {
        this->accept();
    } else {
        DataPublics::showWarning("Save Error\n" + db.lastError().text());
    }
}

void CustomerEditor::on_DeleteButton_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this customer?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        db.exec("DELETE FROM customers WHERE CustomerID = '" + currentID + "'");
        this->accept();
    }
}

void CustomerEditor::on_cmdApplyToAll_clicked()
{
    db.exec("UPDATE products WHERE Customer = '" + currentID + "' SET VAT = '" + ui->cboDefaultVAT->currentText() + "'");
}
