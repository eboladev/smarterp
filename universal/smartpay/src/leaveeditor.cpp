#include "leaveeditor.h"
#include "ui_leaveeditor.h"
#include "datapublics.h"

LeaveEditor::LeaveEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::LeaveEditor)
{
    ui->setupUi(this);
    db = database;
}

LeaveEditor::~LeaveEditor()
{
    delete ui;
}

void LeaveEditor::AddNew(QString AllocationNo)
{
    allocationID = AllocationNo;
    fetchAllocationDetails();
}

void LeaveEditor::Edit(QString LeaveNo)
{
    currentID = LeaveNo;
    fetchAllocationDetails();
}

void LeaveEditor::on_optMultiple_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void LeaveEditor::on_optSingle_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void LeaveEditor::fetchAllocationDetails()
{
    QSqlQuery qu = db.exec("SELECT * FROM employees_leave_allocations WHERE AllocationID = '" + allocationID + "'");
    if (!qu.lastError().isValid()) {
        qu.first();
        QSqlRecord rec = qu.record();
        QString employeeID = qu.record().value("EmployeeID").toString();
        ui->txtEmployeeName->setText(DataPublics::getDbValue("SELECT * FROM vw_employeenames_all WHERE EmployeeID = '" + employeeID + "'", db, "Name").toString());

        ui->txtStartDate->setText(rec.value("StartDate").toDate().toString("dd MMM yyyy"));
        ui->txtEndDate->setText(rec.value("EndDate").toDate().toString("dd MMM yyyy"));
        ui->txtAllocatedDays->setText(rec.value("DaysAllocated").toString());
    }
}
