#include "leavedayswizard.h"
#include "ui_leavedayswizard.h"
#include "datapublics.h"

LeaveDaysWizard::LeaveDaysWizard(QWidget *parent, QSqlDatabase database) :
    QWizard(parent),
    ui(new Ui::LeaveDaysWizard)
{
    ui->setupUi(this);
	db = database;
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
    QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames_all ORDER BY `#` ASC");
    while (qu.next()) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstEmployees);
        it->setText(0, qu.record().value("#").toString());
        it->setText(1, qu.record().value("Name").toString());
        it->setText(99, qu.record().value("EmployeeID").toString());
        it->setCheckState(0, Qt::Unchecked);
    }
    //ui->dtpAdvanceDate->setDate(QDate::currentDate());
    ui->tblAdvances->setColumnHidden(4, true);
}

LeaveDaysWizard::~LeaveDaysWizard()
{
    delete ui;
}


void LeaveDaysWizard::on_commandLinkButton_clicked()
{
    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
    QString quError = "";
    for (int i = 0; i < ui->tblAdvances->rowCount(); i++) {
        QString employeeID = ui->tblAdvances->item(i, 4)->text();
        QString days = ui->tblAdvances->item(i, 2)->text();
        QString amount = ui->tblAdvances->item(i, 3)->text();
        QSqlQuery qu =  db.exec("INSERT INTO leave_days_bought (EmployeeID, MonthID, Days, Amount) VALUES ('"
                + employeeID + "', '"
                + monthID + "', '"
                + days + "', '"
                + amount + "')");
        if (qu.lastError().isValid()) {
            quError.append(qu.lastError().text());
        } else {
            this->accept();
        }
    }

    if (quError.length() > 0) {
        DataPublics::showWarning("An error has occured.\nData not saved");
        //qDebug() << quError;
    }
}


void LeaveDaysWizard::on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    QString employeeID = item->text(99);
    QString employeeName = item->text(1);
    QString rollNo = item->text(0);
    bool exists = false;
    for (int i = 0; i < ui->tblAdvances->rowCount(); i++) {
        if (ui->tblAdvances->item(i, 3)->text() == employeeID) {
            exists = true;
            if (item->checkState(0) == Qt::Checked) {
                ui->tblAdvances->removeRow(i);
                return;
            } else {
                return;
            }
        }
    }
    //Not found
    if (!exists && item->checkState(0) == Qt::Checked) {
        QTableWidgetItem *rollNoItem = new QTableWidgetItem(1);
        QTableWidgetItem *nameItem = new QTableWidgetItem(1);
        QTableWidgetItem *daysItem = new QTableWidgetItem(1);
        QTableWidgetItem *amountItem = new QTableWidgetItem(1);
        QTableWidgetItem *idItem = new QTableWidgetItem(1);

        rollNoItem->setText(rollNo);
        nameItem->setText(employeeName);
        daysItem->setText("0");
        amountItem->setText("0");
        idItem->setText(employeeID);

        int r = ui->tblAdvances->rowCount();
        ui->tblAdvances->insertRow(r);

        ui->tblAdvances->setItem(r, 0, rollNoItem);
        ui->tblAdvances->setItem(r, 1, nameItem);
        ui->tblAdvances->setItem(r, 2, daysItem);
        ui->tblAdvances->setItem(r, 3, amountItem);
        ui->tblAdvances->setItem(r, 4, idItem);
    }

   ui->tblAdvances->setColumnHidden(4, true);
}

void LeaveDaysWizard::on_cboMonths_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
}
