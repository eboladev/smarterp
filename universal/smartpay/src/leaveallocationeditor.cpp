#include "leaveallocationeditor.h"
#include "ui_leaveallocationeditor.h"
#include "datapublics.h"
LeaveAllocationEditor::LeaveAllocationEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::LeaveAllocationEditor)
{
    ui->setupUi(this);
    db = database;
    isAdding = true;

    ui->calEndDate->setDate(QDate::currentDate());
    ui->calStartDate->setDate(QDate::currentDate());

    leaveDays = 0;
}

LeaveAllocationEditor::~LeaveAllocationEditor()
{
    delete ui;
}

void LeaveAllocationEditor::Edit(QString id)
{
    isAdding = false;
    currentID = id;

    QSqlQuery qu = db.exec("SELECT * FROM employees_leave_allocations WHERE AllocationID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning("A database error has occurred:\n\n" + qu.lastError().text());
        this->reject();
    } else {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->calStartDate->setDate(rec.value("StartDate").toDate());
        ui->calEndDate->setDate(rec.value("EndDate").toDate());
        int sat = rec.value("CountSaturdays").toInt();
        int sun = rec.value("CountSundays").toInt();
        ui->spinDays->setValue(rec.value("DaysAllocated").toInt());

        ui->chkSat->setChecked(sat > 0);
        ui->chkSun->setChecked(sun > 0);
    }

    calculateLeaveDays();
}

void LeaveAllocationEditor::AddNew(QString employeeID)
{
    isAdding = true;
    empID = employeeID;
}

void LeaveAllocationEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";

    int sat = 0;
    int sun = 0;

    if (ui->chkSat->isChecked())
        sat = 1;

    if (ui->chkSun->isChecked())
        sun = 0;

    if (isAdding) {
        query = "INSERT INTO employees_leave_allocations (EmployeeID, StartDate, EndDate, CountSaturdays, CountSundays, DaysAllocated) VALUES ('" +
                empID + "', '" +
                DataPublics::mysqlDate(ui->calStartDate->date()) + "', '" +
                DataPublics::mysqlDate(ui->calEndDate->date()) + "', '" +
                QString::number(sat) + "', '" +
                QString::number(sun) + "', '" +
                QString::number(ui->spinDays->value()) + "')";
    } else {
        query = "UPDATE employees_leave_allocations SET "
                " StartDate = '" + DataPublics::mysqlDate(ui->calStartDate->date()) + "', "
                " EndDate = '" + DataPublics::mysqlDate(ui->calEndDate->date()) + "', "
                " CountSaturdays = '" + QString::number(sat) + "', "
                " CountSundays = '" + QString::number(sun) + "', "
                " DaysAllocated = '" + QString::number(ui->spinDays->value()) + "' WHERE AllocationID = '" + currentID + "'";
    }

    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        DataPublics::showWarning("A database error has occurred:\n\n" + qu.lastError().text() + "\n\nPlease try again.");
    } else {
        this->accept();
    }
}

void LeaveAllocationEditor::on_calStartDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    calculateLeaveDays();
}

void LeaveAllocationEditor::on_calEndDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    calculateLeaveDays();
}

void LeaveAllocationEditor::calculateLeaveDays()
{
    QDate startDate = ui->calStartDate->date();
    QDate endDate = ui->calEndDate->date();
    int numDays = 0;
    int diff = startDate.daysTo(endDate);

    for (int i = 0; i <= diff; i++) {
        QDate thisDate = startDate.addDays(i);
        if (thisDate.dayOfWeek() < 6)
            numDays = numDays + 1;

        if ((thisDate.dayOfWeek() == 6) && ui->chkSat->isChecked()) //Sat
            numDays = numDays + 1;

        if ((thisDate.dayOfWeek() == 7) && ui->chkSun->isChecked()) //Sat
            numDays = numDays + 1;
    }

    //ui->lblAllocatedDays->setText(tr("Allocated Leave Days: <b>%1</b>").arg(numDays));
    leaveDays = numDays;
}

void LeaveAllocationEditor::on_chkSat_toggled(bool checked)
{
    Q_UNUSED(checked);
    calculateLeaveDays();
}

void LeaveAllocationEditor::on_chkSun_toggled(bool checked)
{
    Q_UNUSED(checked);
    calculateLeaveDays();
}
