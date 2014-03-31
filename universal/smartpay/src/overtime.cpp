#include "overtime.h"
#include "ui_overtime.h"
#include "datapublics.h"
Overtime::Overtime(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Overtime)
{
    ui->setupUi(this);
    db = database;

    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex", "Month", db, ui->cboMonths);
    scanMonth();

    reloadTable();
}

Overtime::~Overtime()
{
    delete ui;
}

#include "overtime_entryscan.h"
void Overtime::scanMonth()
{
    QString monthName = ui->cboMonths->currentText();
    if (monthName.length() < 1) {
        DataPublics::showWarning("No month selected");
        return;
    }
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    if (monthID.length() < 1) {
        DataPublics::showWarning("No month selected");
        return;
    }

    currentMonth = monthID;

    reloadTable();

}

void Overtime::on_cboMonths_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    scanMonth();
}

void Overtime::reloadTable()
{
    otModel = new QSqlRelationalTableModel(this, db);
    otModel->setTable("misc_hours");
    otModel->setFilter("Month = '" + ui->cboMonths->currentText() + "'");

    QSqlRelation employeeRelation("vw_employeenames_ex", "employeeID", "Name");
    QSqlRelation monthRelation("vw_months_ex", "MonthID", "Month");
    otModel->setRelation(1, employeeRelation);
    otModel->setRelation(2, monthRelation);
    otModel->select();
    otModel->setEditStrategy(QSqlRelationalTableModel::OnRowChange);
    ui->tblMain->setModel(otModel);
    ui->tblMain->setColumnHidden(0, true);
   ui->tblMain->setItemDelegate(new QSqlRelationalDelegate(ui->tblMain));

    ui->tblMain->setAlternatingRowColors(true);
    ui->tblMain->resizeColumnsToContents();
    ui->tblMain->resizeRowsToContents();
}

void Overtime::on_cmdAddNew_clicked()
{
    if (currentMonth.length() > 0) {
        otModel->insertRow(otModel->rowCount());
//        otModel->setData();
    }
}

void Overtime::on_cmdSave_clicked()
{
    otModel->submitAll();
}
