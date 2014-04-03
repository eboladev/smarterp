#include "extendedcalendarwidget.h"
#include "ui_extendedcalendarwidget.h"
#include <QLabel>
#include <QDebug>

ExtendedCalendarWidget::ExtendedCalendarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtendedCalendarWidget)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    redrawMonth();
}

ExtendedCalendarWidget::~ExtendedCalendarWidget()
{
    delete ui;
}

void ExtendedCalendarWidget::on_cmdNextMonth_clicked()
{
    ui->dateEdit->setDate(ui->dateEdit->date().addMonths(1));
    redrawMonth();
}

void ExtendedCalendarWidget::on_cmdPreviousMonth_clicked()
{
    ui->dateEdit->setDate(ui->dateEdit->date().addMonths(-1));
    redrawMonth();
}

void ExtendedCalendarWidget::redrawMonth()
{
    QDate date = ui->dateEdit->date();

    QList<QWidget *> widgets = ui->frame->findChildren<QWidget *>();
    foreach(QWidget * widget, widgets)
    {
        delete widget;
    }

    //QGridLayout *layout = new QGridLayout(ui->frame);
    QStringList daysOfWeek;
    daysOfWeek << "Mon" << "Tue" << "Wed" << "Thu" << "Fri" << "Sat" << "Sun";
    for (int i = 1; i < 8; i++) {
        QLabel *lblDay = new QLabel(ui->frame);
        lblDay->setText(daysOfWeek.at(i - 1));
        QString color = "color: rgb(0, 0, 127)";

        if ((i - 1) > 4) {
            color = "color: rgb(135, 0, 0)";
        }

        lblDay->setStyleSheet("font: 16pt \"MS Shell Dlg 2\";" + color + ";background-color: rgb(255, 255, 255);");
        ui->gridLayout_2->addWidget(lblDay, 0, i - 1, 1, 1, Qt::AlignCenter);
    }

    QDate mDate = date;
    int lastCol;
    int row = 1;
    while (mDate.month() == date.month()) {
        int col = mDate.dayOfWeek() - 1;
        QString color = "color: rgb(0, 0, 127)";

        if ((col) > 4) {
            color = "color: rgb(135, 0, 0)";
        }

        QLabel *lblDay = new QLabel(ui->frame);
        lblDay->setText(QString::number(mDate.day()));
        lblDay->setStyleSheet("font: 16pt \"MS Shell Dlg 2\";" + color + ";background-color: rgb(255, 255, 255);");
        ui->gridLayout_2->addWidget(lblDay, row, col, 1, 1, Qt::AlignCenter);

        lastCol = col;
        if (lastCol > 5)
            row = row + 1;

        mDate = mDate.addDays(1);
    }

}
