#include "salesrepeditor.h"
#include "ui_salesrepeditor.h"

#include "datapublics.h"
SalesRepEditor::SalesRepEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::SalesRepEditor)
{
    ui->setupUi(this);
    db = database;
    isAdding = true;
}

SalesRepEditor::~SalesRepEditor()
{
    delete ui;
}

void SalesRepEditor::addNew()
{
    isAdding = true;
    currentId = "";
    ui->cmdDelete->setVisible(false);
}

void SalesRepEditor::edit()
{
    ui->cmdDelete->setVisible(true);
    isAdding  = false;
    QSqlQuery qu = db.exec("SELECT * FROM salesreps WHERE SalesRepID = '" + currentId + "'");
    if (!qu.lastError().isValid()) {
        qu.first();
        ui->txtFullName->setText(qu.record().value("FullName").toString());
        ui->txtMobile->setText(qu.record().value("MobileNumber").toString());
    }else {
        DataPublics::showWarning("There was an error when fetching the requested information.\n" + qu.lastError().text());
        this->reject();
    }
}

void SalesRepEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";
    if (isAdding) {
        query = tr("INSERT INTO salesreps (FullName, MobileNumber) VALUES ('%1', '%2')").arg(ui->txtFullName->text(), ui->txtMobile->text());
    } else {
        query = tr("UPDATE salesreps SET FullName =  '%1', MobileNumber = '%2' WHERE SalesRepID =  '%3'").arg(ui->txtFullName->text(), ui->txtMobile->text(), currentId);
    }
    db.exec(query);
    if (db.lastError().isValid()) {
        //Error
        DataPublics::showWarning("<h3>Database Error</h3>There was an error while saving the sales rep details:<br/>" + db.lastError().text() + "<br/>Please try again");
    } else {
        //No Error
        DataPublics::showInformation("Sales rep details successfully saved");
        this->accept();
    }
}

void SalesRepEditor::on_cmdDelete_clicked()
{
    if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this sales rep?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
        return;

    QString query = "SELECT NOW()";
    query = tr("DELEte FROM salesreps  WHERE SalesRepID =  '%1'").arg(currentId);
    db.exec(query);
    if (db.lastError().isValid()) {
        //Error
        DataPublics::showWarning("<h3>Database Error</h3>There was an error while deleting the sales rep details:\n" + db.lastError().text() + "\nPlease try again");
    } else {
        //No Error
        DataPublics::showInformation("Sales rep details successfully deleted");
        this->accept();
    }
}

void SalesRepEditor::on_cmdClose_clicked()
{
    this->reject();
}
