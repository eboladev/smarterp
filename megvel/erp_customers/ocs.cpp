#include "ocs.h"
#include "ui_ocs.h"
#include "datapublics.h"
OCs::OCs(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::OCs)
{
    ui->setupUi(this);
    db = database;
    ui->dtpStartDate->setDate(QDate::currentDate().addDays(-31));
    ui->dtpEndDate->setDate(QDate::currentDate());
    ui->checkBox->setChecked(true);
    reloadCustomers();
    reloadOCS();
}

OCs::~OCs()
{
    delete ui;
}

void OCs::reloadOCS()
{
    ocModel = new QSqlQueryModel(this);
    QString ocQuery = "SELECT * FROM vw_ocs2 WHERE `Order Date` BETWEEN '" + DataPublics::mysqlDate(ui->dtpStartDate->date()) + "' AND '" + DataPublics::mysqlDate(ui->dtpEndDate->date()) + "'";
    if (!ui->checkBox->isChecked()) {
        ocQuery = "SELECT * FROM vw_ocs2 WHERE Customer = '" + ui->comboBox->currentText() + "' AND `Order Date` BETWEEN '" + DataPublics::mysqlDate(ui->dtpStartDate->date()) + "' AND '" + DataPublics::mysqlDate(ui->dtpEndDate->date()) + "'";
    }
    ui->treeView->setQuery(ocQuery, db, "Order List (" + ui->dtpStartDate->date().toString("dd-MMM-yyyy") + " to " + ui->dtpEndDate->date().toString("dd-MMM-yyyy") + ")", true);
    ui->treeView->setColumnHidden(0, true);
}

void OCs::on_cmdRefresh_clicked()
{
    reloadOCS();
}


void OCs::reloadCustomers()
{
    DataPublics::loadQueryToComboBox("SELECT * FROM customers", "CompanyName", db, ui->comboBox);
}

#include "publicprinter.h"
#include <QProcess>
void OCs::on_treeView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id = ui->treeView->getCurrentID();
    if (id.length() > 0) {

    }
}
