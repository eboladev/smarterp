#include "leavedaysmw.h"
#include "ui_leavedaysmw.h"
#include "datapublics.h"
LeaveDaysMW::LeaveDaysMW(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::LeaveDaysMW)
{
    ui->setupUi(this);
    db = database;
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);

}

LeaveDaysMW::~LeaveDaysMW()
{
    delete ui;
}

void LeaveDaysMW::on_cboMonths_editTextChanged(const QString &arg1)
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + arg1 + "'", db, "MonthID").toString();
    if (monthID.length() > 0) {
        //QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
        //QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();
        QString query = "SELECT "
                "leave_days_bought.EntryID "
                ", vw_employeenames_ex.Name "
                ", leave_days_bought.Days "
                ", leave_days_bought.Amount "
            "FROM "
                "vw_employeenames_ex "
                "INNER JOIN leave_days_bought  "
                    "ON (vw_employeenames_ex.employeeID = leave_days_bought.EmployeeID) "
                " WHERE leave_days_bought.MonthID =  '" + monthID + "'";
        //qDebug() << query;
        ui->lstLeaves->setQuery(query, db, "Leave Days Issued for " + ui->cboMonths->currentText(), true);
        ui->lstLeaves->setColumnHidden(0, true);
    }
}

#include "leavedayswizard.h"
void LeaveDaysMW::on_actionNew_triggered()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    LeaveDaysWizard *wiz = new LeaveDaysWizard(this, db);
    if (wiz->exec() == QDialog::Accepted) {
        on_cboMonths_editTextChanged(ui->cboMonths->currentText());
    }
}

void LeaveDaysMW::on_cmdDelete_clicked()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    QString id = ui->lstLeaves->getCurrentID();
    if (id.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?",
                                  QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM leave_days_bought WHERE EntryID = '" + id + "'");
            on_cboMonths_editTextChanged(ui->cboMonths->currentText());
        }
    }
}

void LeaveDaysMW::on_cboMonths_currentIndexChanged(const QString &arg1)
{
    on_cboMonths_editTextChanged(arg1);
}
