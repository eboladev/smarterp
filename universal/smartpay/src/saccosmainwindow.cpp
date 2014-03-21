#include "saccosmainwindow.h"
#include "ui_saccosmainwindow.h"




SaccosMainWindow::SaccosMainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::SaccosMainWindow)
{
    ui->setupUi(this);
    db = database;
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);

}

SaccosMainWindow::~SaccosMainWindow()
{
    delete ui;
}

void SaccosMainWindow::on_cmdDelete_clicked()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    QString id = ui->lstSaccos->getCurrentID();
    if (id.length() > 0) {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM sacco_payments WHERE PaymentID = '" + id + "'");
            on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
        }
    }
}

#include "saccoswizerd.h"
void SaccosMainWindow::on_actionNew_Entry_triggered()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    QString closed = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "Closed").toString();
    if (closed == "Yes") {
        DataPublics::showWarning("This month has already been closed.");
        return;
    }
    SaccosWizard *wiz = new SaccosWizard(this, db);
    if (wiz->exec() == QDialog::Accepted) {
        on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());
    }
}

void SaccosMainWindow::on_cboMonths_currentIndexChanged(const QString &arg1)
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + arg1 + "'", db, "MonthID").toString();
    if (monthID.length() > 0) {
        //QString startDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "StartDate").toString();
       // QString endDate = DataPublics::getDbValue("SELECT * FROM months WHERE MonthID = '" + monthID + "'", db, "EndDate").toString();
        QString query = "SELECT "
                "sacco_payments.PaymentID "
                ", vw_employeenames_ex.Name "
                ", sacco_payments.DateIssued "
                ", sacco_payments.Amount "
            "FROM "
                "vw_employeenames_ex "
                "INNER JOIN sacco_payments  "
                    "ON (vw_employeenames_ex.employeeID = sacco_payments.EmployeeID) "
                " WHERE sacco_payments.MonthID =  '" + monthID + "'";
        //qDebug() << query;
        ui->lstSaccos->setQuery(query, db, "SACCO Deductions for " + arg1, true);
        ui->lstSaccos->setColumnHidden(0, true);
    }
}

void SaccosMainWindow::on_actionRefresh_triggered()
{
    on_cboMonths_currentIndexChanged(ui->cboMonths->currentText());

}
