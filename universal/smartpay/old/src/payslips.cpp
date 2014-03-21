#include "payslips.h"
#include "ui_payslips.h"

Payslips::Payslips(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Payslips)
{
    ui->setupUi(this);
    db = database;
    reloadEmployees();
}

Payslips::~Payslips()
{
    delete ui;
}

void Payslips::on_cmdGenerate_clicked()
{

}

void Payslips::reloadEmployees()
{
    ui->lstEmployees->setQuery("SELECT * FROM vw_employeenames", db, "Employees", true);
    ui->lstEmployees->setColumnHidden(0, true);
    ui->lstEmployees->setColumnHidden(1, true);
}

void Payslips::on_checkBox_toggled(bool checked)
{
    if (!checked)
        reloadEmployees();
}
