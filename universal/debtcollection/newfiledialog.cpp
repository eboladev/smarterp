#include "newfiledialog.h"
#include "ui_newfiledialog.h"

#include "publics.h"
NewFileDialog::NewFileDialog(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::NewFileDialog)
{
    ui->setupUi(this);
    db = database;

    Publics::loadDbToComboBox(db, ui->cboCustomers, "SELECT * FROM customers", "CompanyName");

    isAdding = true;
}

NewFileDialog::~NewFileDialog()
{
    delete ui;
}

void NewFileDialog::Edit(QString id)
{
    currentID = id;
    isAdding = false;
    QSqlQuery qu = db.exec("SELECT * FROM collection_files WHERE EntryID = '" + currentID + "'");
    if (!qu.lastError().isValid()) {
        qu.first();
        QString custID = qu.record().value("CustomerID").toString();
        QString comment = qu.record().value("Comment").toString();
        ui->chkCreateNewAction->setVisible(false);
        QString customerName = Publics::getDbValue(db, "SELECT * FROM customers WHERE CustomerID = '" + custID + "'", "CompanyName");
        qDebug() << "Editing file no: " << currentID << " customer id " << custID << " customer name " << customerName;
        ui->txtComment->setPlainText(comment);
        for (int i = 0; i < ui->cboCustomers->count(); i++) {
            if (ui->cboCustomers->itemText(i) == customerName) {
                ui->cboCustomers->setCurrentIndex(i);
            }
        }
    } else {
        Publics::showError(qu.lastError().text());
    }
}

void NewFileDialog::AddNew()
{
    isAdding = true;
}

void NewFileDialog::on_cmdOK_clicked()
{
    QString err;
    QString custID = Publics::getDbValue(db, "SELECT * FROM customers WHERE CompanyName = '" + ui->cboCustomers->currentText() + "'", "CustomerID");
    QString query = "INSERT INTO collection_files (CustomerID, DateOpened, TimeOpened, Comment, Status) VALUES ('"
            + custID + "', "
            + "CURRENT_DATE(), CURRENT_TIME(), '"
            + ui->txtComment->toPlainText() + "', 'Active')";
    if (!isAdding) {
        query = "UPDATE collection_files SET CustomerID = '" + custID + "', "
                " Comment = '" + ui->txtComment->toPlainText() + "' WHERE EntryID = '" + currentID + "'";
    }

    if (Publics::executeQuery(db, query, err)) {
        this->accept();
    } else {
        Publics::showError(err);
    }
}
