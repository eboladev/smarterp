#include "selectdaterange.h"
#include "ui_selectdaterange.h"

SelectDateRange::SelectDateRange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDateRange)
{
    ui->setupUi(this);
    ui->dtpEndDate->setDate(QDate::currentDate());
    ui->dtpStartDate->setDate(QDate::currentDate());
}

SelectDateRange::~SelectDateRange()
{

    delete ui;
}

void SelectDateRange::on_dtpStartDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    changed();
}

void SelectDateRange::changed()
{
    startDate = ui->dtpStartDate->date();
    endDate = ui->dtpEndDate->date();
    isRange = ui->chkRange->isChecked();
}

void SelectDateRange::on_dtpEndDate_dateChanged(const QDate &date)
{
    Q_UNUSED(date);
    changed();
}

void SelectDateRange::on_chkRange_toggled(bool checked)
{
    Q_UNUSED(checked);
    changed();
}
