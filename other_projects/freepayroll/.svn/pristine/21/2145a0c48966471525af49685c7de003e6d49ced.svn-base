#include "calendardateselector.h"
#include "ui_calendardateselector.h"

CalendarDateSelector::CalendarDateSelector(QWidget *parent, QDate def) :
    QDialog(parent),
    ui(new Ui::CalendarDateSelector)
{
    ui->setupUi(this);
    ui->calendarWidget->setSelectedDate(def);
}

CalendarDateSelector::~CalendarDateSelector()
{
    delete ui;
}

void CalendarDateSelector::on_buttonBox_accepted()
{
    dat = ui->calendarWidget->selectedDate();
}
