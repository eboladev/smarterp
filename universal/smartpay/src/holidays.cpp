#include "holidays.h"
#include "ui_holidays.h"
#include "holidayeditor.h"

Holidays::Holidays(QWidget *parent, QSqlDatabase database) :
    QWidget(parent),
    ui(new Ui::Holidays)
{
    ui->setupUi(this);
    db = database;
    reloadHolidays();
}

Holidays::~Holidays()
{
    delete ui;
}

void Holidays::reloadHolidays()
{
    ui->lstHolidays->setQuery("SELECT * FROM holidays", db, "Holidays", true);
    ui->lstHolidays->setColumnHidden(0, true);
}

void Holidays::on_cmdAddNew_clicked()
{
    HolidayEditor *ed = new HolidayEditor(this, db);
    ed->AddNew();
    if (ed->exec() == QDialog::Accepted) {
        reloadHolidays();
    }
}

void Holidays::on_lstHolidays_clicked(const QModelIndex &index)
{
    Q_UNUSED(index);
}

void Holidays::on_lstHolidays_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    if (ui->lstHolidays->getCurrentID().length() < 1) {

    } else {
        HolidayEditor *ed = new HolidayEditor(this, db);
        ed->Edit(ui->lstHolidays->getCurrentID());
        if (ed->exec() == QDialog::Accepted) {
            reloadHolidays();
        }
    }
}

void Holidays::on_cmdDelete_clicked()
{
    if (ui->lstHolidays->getCurrentID().length() < 1) {

    } else {
        if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this holiday?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            db.exec("DELETE FROM holidays WHERE EntryID = '" + ui->lstHolidays->getCurrentID() + "'");
            reloadHolidays();
        }
    }

}
