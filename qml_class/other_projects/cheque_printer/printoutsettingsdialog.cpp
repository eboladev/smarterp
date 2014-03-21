#include "printoutsettingsdialog.h"
#include "ui_printoutsettingsdialog.h"
#include <QtSql>
PrintoutSettingsDialog::PrintoutSettingsDialog(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::PrintoutSettingsDialog), db(database)
{
    ui->setupUi(this);
    model = new SqlTableModel(this, db);

    QSqlQuery qu = db.exec("SELECT * FROM page_settings");
    if (qu.first()) {
        ui->spinPageHeight->setValue(qu.record().value("PageHeight").toDouble());
        ui->spinPageWidth->setValue(qu.record().value("PageWIdth").toDouble());
    }

    reloadFields();
}

PrintoutSettingsDialog::~PrintoutSettingsDialog()
{    
    delete ui;
}

void PrintoutSettingsDialog::reloadFields()
{
    model->setTable("fields");
    model->setEditStrategy(SqlTableModel::OnFieldChange);
    model->select();
    ui->tblFields->setModel(model);
    ui->tblFields->setColumnHidden(0, true);
    ui->tblFields->resizeColumnsToContents();
    ui->tblFields->resizeRowsToContents();
}

void PrintoutSettingsDialog::on_cmdAddField_clicked()
{
    model->insertRows(model->rowCount(), 1);
    //model->setData(model->index(model->rowCount() - 1, 3), "0.00");
    ui->tblFields->resizeRowsToContents();
}

#include <QMessageBox>
void PrintoutSettingsDialog::on_cmdSaveChanges_clicked()
{
    ui->tblFields->selectRow(ui->tblFields->currentIndex().row());
    if (!model->submitAll())
    {
        int ret = QMessageBox::question(this, qApp->applicationName(),
                                        tr("There is a pending transaction in progress. That cannot be commited now."\
                                           "\nError: %1\n"\
                                           "Perform rollback?").arg(model->lastError().text()),
                                        QMessageBox::Yes, QMessageBox::No);
        if(ret == QMessageBox::Yes)
            model->revertAll();
        model->setPendingTransaction(false);
        return;
    }
    model->setPendingTransaction(false);
    ui->tblFields->resizeRowsToContents();
}

void PrintoutSettingsDialog::on_cmdDelete_clicked()
{
    model->removeRows(ui->tblFields->currentIndex().row(), 1);
}

void PrintoutSettingsDialog::on_cmdDefaults_clicked()
{
    db.exec("DELETE FROM fields");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'DTB', 'Account Name', 'Account', '395', '25', '120', '95', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'DTB', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'DTB', 'Cheque Date', 'ChequeDate', '170', '25', '495', '10', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize, WordWrap) VALUES("
            "'DTB', 'Amount In Words', 'AmountInWords', '525', '50', '30', '265', 8, 'Yes')");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'DTB', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");

    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'Other Bank', 'Account Name', 'Account', '395', '25', '120', '95', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'Other Bank', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'Other Bank', 'Cheque Date', 'ChequeDate', '170', '25', '495', '10', 8)");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize, WordWrap) VALUES("
            "'Other Bank', 'Amount In Words', 'AmountInWords', '525', '50', '30', '265', 8, 'Yes')");
    db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
            "'Other Bank', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
    reloadFields();
}

void PrintoutSettingsDialog::on_buttonBox_accepted()
{
    db.exec("DELETE FROM page_settings");
    db.exec("INSERT INTO page_settings (PageHeight, PageWidth) VALUES ('"
            + QString::number(ui->spinPageHeight->value()) + "', '"
            + QString::number(ui->spinPageWidth->value()) + "')");
    on_cmdSaveChanges_clicked();
    this->accept();
}

#include <QInputDialog>
void PrintoutSettingsDialog::on_cmdAddProfile_clicked()
{
    QString profileName = QInputDialog::getText(this, "New Profile", "Profile Name:");
    if (profileName.length() > 0) {
        db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                "'" + profileName   + "', 'Account Name', 'Account', '395', '25', '120', '95', 8)");
        db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                "'" + profileName   + "', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
        db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                "'" + profileName   + "', 'Cheque Date', 'ChequeDate', '170', '25', '495', '10', 8)");
        db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize, WordWrap) VALUES("
                "'" + profileName   + "', 'Amount In Words', 'AmountInWords', '525', '50', '30', '265', 8, 'Yes')");
        db.exec("INSERT INTO fields (Profile, Description, Column, Width, Height, X, Y, FontSize) VALUES("
                "'" + profileName   + "', 'Amount', 'LocaleAmount', '135', '25', '495', '90', 8)");
        reloadFields();
    }
}
