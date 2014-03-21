#include "payslips.h"
#include "ui_payslips.h"
#include "qtprinter.h"
Payslips::Payslips(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Payslips)
{
    ui->setupUi(this);
    db = database;
    if (db.isOpen()) {
        reloadMonths();
        reloadEmployees();
    }
    //ui->widget->db = db;

    ui->trvEmployees->setVisible(false);
    ui->trvMonths->setVisible(false);
}

Payslips::~Payslips()
{
    delete ui;
}

void Payslips::on_cmdGenerate_clicked()
{
    QString monthID = ui->lstMonths->getCurrentID();
    QString monthWhere = "";
    QString param_where = " WHERE ";
    QString empWhere = "";
    //Build monthWhere
    if (ui->checkBox->isChecked()) {
        //No monthID where
        monthWhere = "";
    } else {
        monthWhere = " MonthID = '" + monthID + "'";
        if (monthID.length() < 1) {
            monthWhere = "";
        }
    }
    //Build employee where
    if (ui->chkGenerate->isChecked()) {
        empWhere = "";
    } else {
        empWhere = " EmployeeID = '" + ui->lstEmployees->getCurrentID() + "'";
        if (ui->lstEmployees->getCurrentID().length() < 1)
            empWhere = "";
    }
    //    for (int i = 0; i < ui->lstEmployees->myModel->rowCount(); i++) {
    //        if (ui->lstEmployees
    //    }


    if (monthWhere.length() < 1 && empWhere.length() < 1) {
        param_where = "";
    }
    if (monthWhere.length() > 0 && empWhere.length() >0) {
        param_where = param_where + " " + monthWhere + " AND " + empWhere;
    }
    if (monthWhere.length() > 0 && empWhere.length() < 1) {
        param_where = param_where + " " + monthWhere;
    }
    if (monthWhere.length() < 1 && empWhere.length() > 0) {
        param_where = param_where + " " + empWhere;
    }

    //ui->widget->loadReport("Payslips4x1", param_where);
    //ui->widget->loadReport("Payslips4x1?", "");

    QtPrinter *qp = new QtPrinter(this, db, param_where, "Payslips4x1");

    Q_UNUSED(qp);
}

void Payslips::reloadEmployees()
{
    ui->lstEmployees->setQuery("SELECT * FROM vw_employeenames", db, "Employees", true);
    ui->lstEmployees->setColumnHidden(0, true);
    ui->lstEmployees->setColumnHidden(1, true);

    QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames");
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvEmployees);
            it->setText(99, qu.record().value("EmployeeID").toString());
            it->setText(0, qu.record().value("#").toString());
            it->setText(1, qu.record().value("Name").toString());
            it->setCheckState(0, Qt::Unchecked);
        }
    }
}

void Payslips::reloadMonths()
{
    ui->lstMonths->setQuery("SELECT MonthID, MonthName as 'Month', Year FROM months", db, "Payroll Months", true);
    ui->lstMonths->setColumnHidden(0, true);

    QSqlQuery qu = db.exec("SELECT MonthID, Concat(Year, ' ', MonthName) as 'Month', Year FROM months");
    if (!qu.lastError().isValid()) {
        while (qu.next()) {
            QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvMonths);
            it->setText(99, qu.record().value("MonthID").toString());
            it->setText(0, qu.record().value("Month").toString());
            it->setCheckState(0, Qt::Unchecked);
        }
    }
}

void Payslips::on_checkBox_toggled(bool checked)
{
    if (!checked)
        reloadEmployees();
}
