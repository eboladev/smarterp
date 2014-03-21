#include "customdeductionswizard.h"
#include "ui_customdeductionswizard.h"
#include "datapublics.h"

CustomDeductionsWizard::CustomDeductionsWizard(QWidget *parent, QSqlDatabase database) :
    QWizard(parent),
    ui(new Ui::CustomDeductionsWizard)
{
    ui->setupUi(this);
    db = database;

    QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames_ex");
    while (qu.next()) {
        QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstEmployees);
        // it->setText(0, qu.record().value("#").toString());
        it->setText(1, qu.record().value("Name").toString());
        it->setText(99, qu.record().value("EmployeeID").toString());
        it->setCheckState(0, Qt::Unchecked);
    }
    ui->dtpIssueDate->setDate(QDate::currentDate());
    ui->tblDeductions->setColumnHidden(3, true);
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonth);
}

CustomDeductionsWizard::~CustomDeductionsWizard()
{
    delete ui;
}

void CustomDeductionsWizard::on_commandLinkButton_clicked()
{
    QString quError = "";
    for (int i = 0; i < ui->tblDeductions->rowCount(); i++) {
        QString employeeID = ui->tblDeductions->item(i, 3)->text();
        QString advance = ui->tblDeductions->item(i, 2)->text();
        QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonth->currentText() + "'", db, "MonthID").toString();
        QString deductionType = ui->cboDeductionType->currentText();

        QSqlQuery qu =  db.exec("INSERT INTO custom_deductions (EmployeeID, MonthID, Amount, Type, DateIssued) VALUES ('"
                                + employeeID + "', '"
                                + monthID  + "', '"
                                + advance  + "', '"
                                + deductionType  + "', '"
                                + ui->dtpIssueDate->date().toString("yyyy-MM-dd") + "')");
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


void CustomDeductionsWizard::on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    QString employeeID = item->text(99);
    QString employeeName = item->text(1);
    QString rollNo = item->text(0);
    bool exists = false;
    for (int i = 0; i < ui->tblDeductions->rowCount(); i++) {
        if (ui->tblDeductions->item(i, 3)->text() == employeeID) {
            exists = true;
            if (item->checkState(0) == Qt::Checked) {
                ui->tblDeductions->removeRow(i);
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
        QTableWidgetItem *AdvanceItem = new QTableWidgetItem(1);
        QTableWidgetItem *idItem = new QTableWidgetItem(1);

        rollNoItem->setText(rollNo);
        nameItem->setText(employeeName);
        AdvanceItem->setText(QString::number(ui->spinAmount->value()));
        idItem->setText(employeeID);

        int r = ui->tblDeductions->rowCount();
        ui->tblDeductions->insertRow(r);

        ui->tblDeductions->setItem(r, 0, rollNoItem);
        ui->tblDeductions->setItem(r, 1, nameItem);
        ui->tblDeductions->setItem(r, 2, AdvanceItem);
        ui->tblDeductions->setItem(r, 3, idItem);
    }

    ui->tblDeductions->setColumnHidden(3, true);
}
