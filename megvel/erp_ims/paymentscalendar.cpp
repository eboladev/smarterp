#include "paymentscalendar.h"
#include "ui_paymentscalendar.h"

PaymentsCalendar::PaymentsCalendar(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::PaymentsCalendar)
{
    ui->setupUi(this);
    db = database;
    cDate = QDate::currentDate();

    ui->cboMonth->setCurrentIndex(QDate::currentDate().month() - 1);
    ui->cboYear->setCurrentText(QString::number(QDate::currentDate().year()));

    autoMonth();
}

PaymentsCalendar::~PaymentsCalendar()
{
    delete ui;
}

void PaymentsCalendar::autoMonth()
{
    ui->cboMonth->setCurrentIndex(cDate.month() - 1);
    ui->cboYear->setCurrentText(QString::number(cDate.year()));
}

void PaymentsCalendar::autocDate()
{
    cDate.setDate(ui->cboYear->currentText().toInt(), ui->cboMonth->currentIndex() + 1, 1);
}

void PaymentsCalendar::on_cmdPreviousMonth_clicked()
{
    cDate = cDate.addMonths(-1);
    autoMonth();
}

void PaymentsCalendar::on_cmdNextMonth_clicked()
{
    cDate = cDate.addMonths(1);
    autoMonth();
}

void PaymentsCalendar::redrawCalendar()
{
    QString html = "<html><head><h1>Payments Calendar For " + ui->cboMonth->currentText() + " "
            + ui->cboYear->currentText() + "</h1>";
    html +=  " <style type=\"text/css\"> "
            " table.gridtable { "
            "font-family: verdana,arial,sans-serif; "
            "font-size:11px; "
            "color:#333333; "
            "border-width: 1px; "
            "border-color: #666666; "
            " border-collapse: collapse; "
            " } "
            "table.gridtable th { "
            "border-width: 1px; "
            " padding: 8px; "
            " border-style: solid; "
            " border-color: #666666; "
            " background-color: #dedede; "
            "} "
            " table.gridtable td { "
            " border-width: 1px; "
            "padding: 8px; "
            " border-style: solid; "
            " border-color: #666666; "
            " background-color: #ffffff; "
            " } "
            " </style></head><body>";

    QDate monthStartDate = QDate(ui->cboYear->currentText().toInt(), ui->cboMonth->currentIndex() + 1, 1);

    QDate monthEndDate;
    int end = 32;
    bool valid = false;
    while (!valid) {
        monthEndDate = QDate(ui->cboYear->currentText().toInt(), ui->cboMonth->currentIndex() + 1, end);
        valid = monthEndDate.isValid();
        qDebug() << monthEndDate << valid;
        end = end - 1;
    }

    html += "<h3>" + monthStartDate.toString("dd MMMM yyyy")+ "-" + monthEndDate.toString("dd MMMM yyyy")+ "</h3>";


    int dayCount = monthStartDate.daysTo(monthEndDate) + 1;

    int weeks = dayCount / 7;
    if ((weeks * 7) < dayCount){
        weeks = weeks+1;
    }

    QLocale loc(QLocale::English, QLocale::Kenya);

    QStringList  weeksList;
    QString table = "<table class=\"gridtable\" width=100%>";
    int days = 0;
    for (int i = 0; i < weeks; i++) {
        int weekNum = i  + 1;
        QString weekName = "Week " + QString::number(weekNum);
        weeksList.append(weekName);
        table += "<tr><td><b>" + weekName + "</b></td>";
        for (int d = 0; d < 7; d++) {
            if (days < dayCount) {
                QDate currentDay = monthStartDate.addDays(days);
                QString dateLabel = "<b>" +
                        currentDay.toString("ddd") + " " +
                        QString::number(currentDay.day()) + "-" +
                        currentDay.toString("MMM") + "-" +
                        currentDay.toString("yy")
                        + "</b>";
                QString presence = "---";
                QString bgColor = "\"white\"";
                QSqlQuery qu =  db.exec("SELECT * FROM ims.vw_calendar WHERE InvoicePaymentDateDue = '" + currentDay.toString("yyyy-MM-dd") + "'");
                if (qu.size() < 1) {
                    presence = "---";
                } else {
                    bgColor = "yellow";
                    presence = "";
                    while (qu.next()) {
                        presence = presence + "<p>"
                                "<b>File No:</b> " + qu.record().value("FileNo").toString()
                                + "<br/><b>Shipment:</b>" + qu.record().value("ShipmentName").toString() + ""
                                + "<br/><b>Invoice No:</b>" + qu.record().value("InvoiceNo").toString()
                                + "<br/><b>Amount:</b>" + loc.toString(qu.record().value("InvoiceAmount").toDouble())
                                + "<br/></br>________</p>";
                    }
                }
                days++;
                table += "<td bgcolor=" + bgColor + ">" + dateLabel;
                table += "<br/>" + presence;
                table += "</td>";
            }
        }
        table += "</tr>";
    }
    table += "</table>";
    html += table;
    html += "</table>";

    html += "</body>";
    ui->txtCalendar->setHtml(html);
}

void PaymentsCalendar::on_cboMonth_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    autocDate();
    redrawCalendar();
}

void PaymentsCalendar::on_cboYear_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    autocDate();
    redrawCalendar();
}
