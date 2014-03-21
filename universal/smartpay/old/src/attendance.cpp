#include "attendance.h"
#include "ui_attendance.h"

#include "uploadattendance.h"
#include "publics.h"
#include "hourcalculator.h"
#include "recalculateattendance.h"
#include "manualclockin.h"
#include "datapublics.h"
#include "createregister.h"

Attendance::Attendance(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Attendance)
{
    ui->setupUi(this);
    db = database;
    reloadAttendance();
    reloadEmployees();
    ui->StartDate->setDate(QDate::currentDate());
    ui->EndDate->setDate(QDate::currentDate());
    ui->dtpPast->setDate(QDate::currentDate());
    ui->DailySignIn->db = db;
    ui->AttStartDate->setDate(QDate::currentDate());
    ui->AttEndDate->setDate(QDate::currentDate());
}

Attendance::~Attendance()
{
    delete ui;
}

void Attendance::on_UploadAttendance_clicked()
{
    UploadAttendance up(this, db);
    if (up.exec()) {
        reloadAttendance();
    }
}

void Attendance::on_dtpPast_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    reloadAttendance();
}

void Attendance::reloadAttendance()
{
    ui->lstAttendance->setQuery("SELECT * FROM `vw_attendance` WHERE `Date` = '" + DataPublics::mysqlDate(ui->dtpPast->date()) + "' ORDER BY `Name` ASC"
                                , db , "Attendance For " + ui->dtpPast->date().toString("dd-MMM-yyyy"), true);
    ui->lstAttendance->setColumnHidden(0, true);
}

void Attendance::reloadEmployees()
{
    Publics::loadDbToComboBox(db, "SELECT * FROM vw_employeenames", "Name", ui->Employee);
}

void Attendance::recalculateEmployee()
{
    QString empID = Publics::getDbValue(db, "SELECT EmployeeID FROM vw_employeenames WHERE Name = '" + ui->Employee->currentText() + "'", "EmployeeID");
    QString startDate = Publics::getDateString(ui->StartDate->date());
    QString endDate = Publics::getDateString(ui->EndDate->date());
    HourCalculator::RecalculateEmployeeHours(empID, startDate, endDate, db);
    showEmployeeAttendance();
}

void Attendance::showEmployeeAttendance()
{
    QString empID = Publics::getDbValue(db, "SELECT `EmployeeID` FROM `vw_employeenames` WHERE `Name` = '" + ui->Employee->currentText() + "'", "EmployeeID");
    QString startDate = Publics::getDateString(ui->StartDate->date());
    QString endDate = Publics::getDateString(ui->EndDate->date());
    ui->lst_EmployeeAttendance->setQuery("SELECT * FROM `vw_attendance_ex` WHERE `employeeID` = '" + empID + "' AND `Date` BETWEEN '" + startDate +"' AND '"+ endDate +"'", db, "Employee Attendence", true);
    ui->lst_EmployeeAttendance->setColumnHidden(0, true);
    ui->lst_EmployeeAttendance->setColumnHidden(1, true);
}

void Attendance::on_ShowEmployeeAttendance_clicked()
{
    showEmployeeAttendance();
}

void Attendance::on_RecalculateEmployeeAttendance_clicked()
{
    recalculateEmployee();
}

void Attendance::on_AttShowReport_clicked()
{
    ui->lstAttendanceReport->setQuery("SELECT * FROM vw_attendance_ex WHERE `Date` BETWEEN '" + Publics::getDateString(ui->AttStartDate->date()) + "' AND '" + Publics::getDateString(ui->AttEndDate->date()) + "' ORDER BY `Date`", db, "Attendance Report", true);
    ui->lstAttendanceReport->setColumnHidden(1, true);
}

void Attendance::on_RecalculateAllAttendance_clicked()
{
    RecalculateAttendance rec(this, db);
    if (rec.exec()) {

    }
}

void Attendance::on_GenerateDailySignInSheets_clicked()
{
    ui->DailySignIn->loadReport("EmployeesDepartments", "");
}

void Attendance::on_ManualClockin_clicked()
{
    ManualClockIn *cl = new ManualClockIn(this, db);
    if (cl->exec()) {
        reloadAttendance();
    }
}

void Attendance::on_cmdCreateRegister_clicked()
{
    CreateRegister *reg = new CreateRegister(this, db);
    if (
    reg->exec() ) {
        reloadAttendance();
    }

}
