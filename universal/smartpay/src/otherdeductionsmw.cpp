#include "otherdeductionsmw.h"
#include "ui_otherdeductionsmw.h"
#include "datapublics.h"
#include "customdeductionswizard.h"
OtherDeductionsMW::OtherDeductionsMW(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::OtherDeductionsMW)
{
    ui->setupUi(this);
    db = database;
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonth);
    reloadDeductions();
}

OtherDeductionsMW::~OtherDeductionsMW()
{
    delete ui;
}

void OtherDeductionsMW::reloadDeductions()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonth->currentText() + "'", db, "MonthID").toString();
    QString query = " SELECT "
            "`custom_deductions`.`DeductionID`"
            ", `vw_employeenames_ex`.`Name`"
            ", `months`.`MonthName`"
            ", `months`.`Year`"
            ", `custom_deductions`.`DateIssued`"
            ", `custom_deductions`.`Type`"
            ", `custom_deductions`.`Amount`"
        " FROM "
            " `custom_deductions` "
            " INNER JOIN `vw_employeenames_ex` "
            "    ON (`custom_deductions`.`EmployeeID` = `vw_employeenames_ex`.`employeeID`)"
            " INNER JOIN `months` "
            "    ON (`custom_deductions`.`MonthID` = `months`.`MonthID`) "
            " WHERE `custom_deductions`.`MonthID` = '" + monthID + "'";

    ui->trvDeductions->setQuery(query, db, "Custom Monthly Deductions For " + ui->cboMonth->currentText(), true);
    ui->trvDeductions->setColumnHidden(0, true);
}

void OtherDeductionsMW::on_cboMonth_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    reloadDeductions();
}

void OtherDeductionsMW::on_actionNew_Entries_triggered()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonth->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    CustomDeductionsWizard *wiz = new CustomDeductionsWizard(this, db);
    if (wiz->exec() == QDialog::Accepted)
        reloadDeductions();
}

void OtherDeductionsMW::on_pushButton_clicked()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonth->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    QString id = ui->trvDeductions->getCurrentID();
    if (id.length() > 0) {
        if (QMessageBox::question(this , "Confirm Delete", "Are you sure you want to delete this deduction?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM custom_deductions WHERE DeductionID = '" + id+ "'");
            reloadDeductions();
        }
    }
}
