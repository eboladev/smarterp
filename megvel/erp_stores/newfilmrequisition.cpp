#include "newfilmrequisition.h"
#include "ui_newfilmrequisition.h"
#include "datapublics.h"
NewFilmRequisition::NewFilmRequisition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFilmRequisition)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    DataPublics::loadQueryToComboBox("SELECT * FROM customers", "CompanyName", db, ui->cboCustomer);
    ui->cboProduct->addItem("Select a customer");
    DataPublics::loadQueryToComboBox("SELECT * FROM salesreps", "FullName", db, ui->cboSalesRep);
}

NewFilmRequisition::~NewFilmRequisition()
{
    delete ui;
}

void NewFilmRequisition::on_cmdCancel_clicked()
{
    this->reject();
}

void NewFilmRequisition::on_cmdOK_clicked()
{


    //

    this->accept();
}

void NewFilmRequisition::on_cboCustomer_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase db = QSqlDatabase::database();
    QString customerID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + arg1 + "'", db, "CustomerID").toString();
    QString salesRepID = DataPublics::getDbValue("SELECT * FROM customers WHERE CompanyName = '" + arg1 + "'", db, "SalesRep").toString();
    QString salesRepFullName = DataPublics::getDbValue("SELECT FullName FROM salesreps WHERE SalesRepID = '" + salesRepID + "'", db, "FullName").toString();

#if QT_VERSION >= 0x050000
    ui->cboSalesRep->setCurrentText(salesRepFullName);
#endif
#if QT_VERSION < 0x50000
    for (int s = 0; s < ui->cboSalesRep->count(); s++) {
        if (ui->cboSalesRep->itemText(s) == salesRepFullName)
            ui->cboSalesRep->setCurrentIndex(s);
    }
#endif
    ui->cboProduct->clear();
    DataPublics::loadQueryToComboBox("SELECT Product FROM products WHERE Customer = '" + customerID + "'", "Product", db, ui->cboProduct);
}
