#include "holidayeditor.h"
#include "ui_holidayeditor.h"
#include <QMessageBox>

HolidayEditor::HolidayEditor(QWidget *parent, QSqlDatabase database) :
    QDialog(parent),
    ui(new Ui::HolidayEditor)
{
    ui->setupUi(this);
    db = database;
    isAdding = false;
}

HolidayEditor::~HolidayEditor()
{
    delete ui;
}

void HolidayEditor::Edit(QString id)
{
    currentID = id;
    isAdding = false;

    QSqlQuery qu = db.exec("SELECT * FROM holidays WHERE EntryID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        QMessageBox::critical(this, "Database Error", qu.lastError().text());
        this->reject();
    } else {
        qu.first();
        QSqlRecord rec = qu.record();
        ui->txtHolidayName->setText(rec.value("HolidayName").toString());
        ui->cboDay->setEditText(rec.value("Day").toString());
        ui->cboMonth->setEditText(rec.value("Month").toString());
        ui->cboYear->setEditText(rec.value("Year").toString());
    }

}

void HolidayEditor::AddNew()
{
    isAdding = true;
}

void HolidayEditor::on_cmdSave_clicked()
{
    QString query = "SELECT NOW()";

    if (isAdding) {
        query = "INSERT INTO holidays (HolidayName, Day, Month, Year) VALUES ('"
                + ui->txtHolidayName->text() + "', '"
                + ui->cboDay->currentText()  + "', '"
                + ui->cboMonth->currentText()  + "', '"
                + ui->cboYear->currentText() + "')";
    } else {
        query = "UPDATE holidays SET HolidayName = '" +
                ui->txtHolidayName->text() + "', "
                " Day = '" + ui->cboDay->currentText() + "', "
                " Month = '" + ui->cboMonth->currentText() + "', "
                " Year = '" + ui->cboYear->currentText() + "' WHERE EntryID = '" + currentID + "'";
    }

    QSqlQuery qu = db.exec(query);
    if (!qu.lastError().isValid()) {
        this->accept();
    } else {
        QMessageBox::critical(this, "Database Error", "A database error has occured.\n\n" + qu.lastError().text());
    }
}
