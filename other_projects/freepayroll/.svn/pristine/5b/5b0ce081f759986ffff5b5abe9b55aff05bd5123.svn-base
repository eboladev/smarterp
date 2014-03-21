#include "payrollapi.h"

#include <QMessageBox>
#include "calendardateselector.h"
#include <QLineEdit>
PayrollAPI::PayrollAPI(QObject *parent) :
    QObject(parent)
{
}

void PayrollAPI::showError(QString error, QWidget *parent, QString title)
{
    QMessageBox::critical(parent, title, error);
}

QString PayrollAPI::selectDateFromCalendar(QDate defaultDate)
{
    CalendarDateSelector *wid = new CalendarDateSelector(0, defaultDate);
    if (wid->exec() == QDialog::Accepted) {
        return wid->dat.toString("dd MMM yyyy");
    }
    return defaultDate.toString("dd MMM yyyy");
}

void PayrollAPI::setLineEditDate(QLineEdit *txt)
{
    QDate defDate = QDate::currentDate();
    if (txt->text().length() > 0) {
        //Not empty
        QDate tmpDate = QDate::fromString(txt->text(), "dd MMM yyyy");
        if (tmpDate.isValid())
            defDate = tmpDate;
    }
    QString newDat = selectDateFromCalendar(defDate);
    txt->setText(newDat);
}
