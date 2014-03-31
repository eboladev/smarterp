#include "manualclockin.h"
#include "ui_manualclockin.h"
#include "datapublics.h"
#include "threadedmanualclockinout.h"

ManualClockIn::ManualClockIn(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::ManualClockIn)
{
    ui->setupUi(this);
    db = database;
    ui->dtpDate->setDate(QDate::currentDate());
    ui->dtpTime->setTime(QTime::currentTime());
    loadEmployees();
}

ManualClockIn::~ManualClockIn()
{
    delete ui;
}

void ManualClockIn::loadEmployees()
{
    DataPublics::LoadQueryToTreeWidget("SELECT * FROM vw_employeenames", db, ui->lstEmployees, true, Qt::Unchecked, 1);
    ui->lstEmployees->setColumnHidden(0, true);
    ui->lstEmployees->setAlternatingRowColors(true);
}

void ManualClockIn::on_cmdSave_clicked()
{
    QStringList employees;
    for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++) {
        QTreeWidgetItem *it = ui->lstEmployees->invisibleRootItem()->child(i);
        if (it->checkState(1) == Qt::Checked)
            employees.insert(employees.count(), it->text(0));
    }
    ThreadedManualClockInOut *th = new ThreadedManualClockInOut(this);
    bool inOut = true;
    if (ui->optOut->isChecked())
        inOut = false;
    th->setVars(db, employees, ui->dtpDate->date(), inOut, ui->dtpTime->time());
    connect (th, SIGNAL(showPercentage(int)), ui->progressBar, SLOT(setValue(int)));
    th->run();
}

void ManualClockIn::on_SelectAll_clicked()
{
    for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++)
        ui->lstEmployees->invisibleRootItem()->child(i)->setCheckState(1, Qt::Checked);
}

void ManualClockIn::on_SelectNone_clicked()
{
    for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++)
        ui->lstEmployees->invisibleRootItem()->child(i)->setCheckState(1, Qt::Unchecked);
}
