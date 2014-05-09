#include "customereditor.h"
#include "ui_customereditor.h"
#include "datapublics.h"
CustomerEditor::CustomerEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerEditor)
{
    ui->setupUi(this);
    isAdding = true;
    db = QSqlDatabase::database("closures");
    DataPublics::loadQueryToComboBox("SELECT * FROM salesreps", "FullName", db, ui->SalesRep);
    DataPublics::loadQueryToComboBox("SELECT * FROM salesreps", "FullName", db, ui->SecondarySalesRep);
    ui->DeleteButton->setVisible(false);
    ui->CompanyName->setReadOnly(false);
    ui->lblChange->setVisible(false);
}

CustomerEditor::~CustomerEditor()
{
    delete ui;
}

void CustomerEditor::edit(QString customerID)
{    
    ui->CompanyName->setReadOnly(true);
    ui->DeleteButton->setVisible(true);
    ui->lblChange->setVisible(true);
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
        QString tmpQuery = "INSERT INTO customers (CompanyName) VALUES ('" +  ui->CompanyName->text()+ "')";
        QSqlQuery tmpQu = db.exec(tmpQuery);
        if (!tmpQu.lastError().isValid()) {
            currentID = tmpQu.lastInsertId().toString();
            isAdding  =false;
        } else {
            DataPublics::showWarning("Save Error\n" + tmpQu.lastError().text());
            return;
        }
    }

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

    saveQuery.append(
                tr(",CreditLimit = '%3', StatementEmail = '%2', MinimumRP = '%3' ")
                .arg(
                    ui->CreditLimit->text(),
                    ui->StatementsEmail->text(),
                    ui->MinimumRP->text()
                    ));

    QString salesRepID = DataPublics::getDbValue("SELECT * FROM salesreps WHERE FullName = '" + ui->SalesRep->currentText() + "'", db, "SalesRepID").toString();

    saveQuery.append(tr(",SalesRep = '%1', Second = '%2'  ")
                     .arg(salesRepID, ui->SecondarySalesRep->currentText()
                          )
                     );

    saveQuery.append(", quickbooks_updated = 'No' WHERE CustomerID = '" + currentID + "'");


    if (!db.exec(saveQuery).lastError().isValid()) {
        emit reload();
        edit(currentID);
    } else {
        DataPublics::showWarning("Save Error\n" + db.lastError().text());
    }

}

#include <QMessageBox>
void CustomerEditor::on_DeleteButton_clicked()
{
    if (currentID.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this customer?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("UPDATE customers SET deleted = 'Yes' WHERE CustomerID = '" + currentID + "'");
            if (db.lastError().isValid()) {
                QMessageBox::critical(this, "Error", db.lastError().text());
                return;
            } else {
                emit reload();
                this->accept();
            }
        }
    }
}

#include <QInputDialog>
void CustomerEditor::on_lblChange_linkActivated(const QString &link)
{
    Q_UNUSED(link);
    QInputDialog *dlg = new QInputDialog(this);
    QString newName =  dlg->getText(this, "Name Change", "Enter the new company name:", QLineEdit::Normal, ui->CompanyName->text());
    if (newName.length() > 0)    {
        if (newName != ui->CompanyName->text()) {
            QString oldName = ui->CompanyName->text();
            ui->CompanyName->setText(newName);
            on_SaveButton_clicked();


//            db.exec("INSERT INTO customer_name_changes (customer_id, old_name, new_name, "
//                    " date, time) VALUES ('"
//                    + currentID + "', '"
//                    +

        }
    }
}
