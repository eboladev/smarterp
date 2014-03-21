#include "extendednewaction.h"
#include "ui_extendednewaction.h"
ExtendedNewAction::ExtendedNewAction(QWidget *parent,QList <Calendar *> *calendars) :
    QDialog(parent),
    ui(new Ui::ExtendedNewAction)
{
    ui->setupUi(this);

    Publics::loadDbToComboBox(Publics::getDatabase(), ui->cboCustomer, "SELECT * FROM customers", "CompanyName");
    ui->dtpDate->setDate(QDate::currentDate());
    ui->dtpNextDate->setDate(QDate::currentDate());
    ui->dtpTime->setTime(QTime::currentTime());
    ui->dtpNextTime->setTime(QTime::currentTime());

    ui->dtpTime->setVisible(false);

    ptrCalendars = new QList <Calendar *>();
    QListIterator <Calendar *> i(*calendars);
    int j = 0;
    while(i.hasNext())
    {
        Calendar *cal = i.next();
        if(cal->isSelected())
        {
            QPixmap map(16,16);
            map.fill(cal->color());
            QIcon icon(map);
            ui->cboNextCalendar->addItem(icon, cal->name(), cal->key());
            ptrCalendars->append(cal);
            j++;
        }
    }
}

ExtendedNewAction::~ExtendedNewAction()
{
    delete ui;
}

void ExtendedNewAction::setCustomer(QString custName)
{
    for (int i = 0; i < ui->cboCustomer->count(); i++) {
        if (ui->cboCustomer->itemText(i) == custName)
            ui->cboCustomer->setCurrentIndex(i);
    }
    loadCustomerAgeing();
}

void ExtendedNewAction::loadCustomerAgeing()
{
   // QString customerID = Publics::getDbValue(Publics::getDatabase(), "SELECT CustomerID FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'", "CustomerID");
   // if (customerID.length() > 0) {
        QSqlQuery qu = Publics::getDatabase().exec("SELECT * FROM customer_balances WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'");
        if (qu.lastError().isValid()) {
            Publics::showError(qu.lastError().text());
        } else {
            qu.first();
            QString ageingText = "<table width=100% border=0>";
            ageingText += "<tr><td><b>Current Balance:</b></td><td>" + QString("%L1").arg(qu.record().value("CurrentBalance").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>0-30 Days:</b></td><td>" + QString("%L1").arg(qu.record().value("30").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>30-60 Days:</b></td><td>" + QString("%L1").arg(qu.record().value("60").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>60-90 Days:</b></td><td>" + QString("%L1").arg(qu.record().value("90").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>90-120 Days:</b></td><td>" + QString("%L1").arg(qu.record().value("120").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>120+ Days:</b></td><td>" + QString("%L1").arg(qu.record().value("Over120").toDouble(), 2, 'f', 2) + "</td></tr>";
            ageingText += "<tr><td><b>Total:</b></td><td>" + QString("%L1").arg(qu.record().value("Total").toDouble(), 2, 'f', 2) + "</td></tr>";

            ageingText += "</table>";
            //QString("%L1").arg(txt.toDouble(), 2, 'f', 2)
            ui->textBrowser->setHtml(ageingText);
        }
  //  }
}

void ExtendedNewAction::on_cmdSave_clicked()
{
    QString customerID = Publics::getDbValue(Publics::getDatabase(), "SELECT CustomerID FROM customers WHERE CompanyName = '" + ui->cboCustomer->currentText() + "'", "CustomerID");
    if (customerID.length() > 0) {
        QDate startDate = ui->dtpDate->date();
        QTime startTime = ui->dtpTime->time();
        QTime endTime = ui->dtpTime->time().addSecs(3600);
        QSqlQuery qu = Publics::getDatabase().exec("INSERT INTO appointments (AppointmentType, CustomerID, "
                                                   " StartDate, StartTime, EndDate, EndTime, Location, Subject, Description) VALUES ('1', '"
                                                   + customerID + "', '"
                                                   + startDate.toString("yyyy-MM-dd")  + "', '"
                                                   + startTime.toString("HH:mm:ss") + "', '"
                                                   + startDate.toString("yyyy-MM-dd")  + "', '"
                                                   + endTime.toString("HH:mm:ss") + "', '"
                                                   + "Office"  + "', '"
                                                   + ui->cboSubject->currentText()  + "', '"
                                                   + ui->txtNotes->toPlainText()  + "'"
                                                   + ")");
        if (qu.lastError().isValid()) {
            Publics::showError(qu.lastError().text());
        } else {
            if (ui->checkBox->isChecked()) {
                //Next appointment planned...
                Appointment *app = new Appointment();
                app->setCalendar(ptrCalendars->at(ui->cboNextCalendar->currentIndex()));
                app->setCalendarKey(ptrCalendars->at(ui->cboNextCalendar->currentIndex())->key());
                app->setCustomerID(customerID);

                QDate startDate = QDate::fromString(ui->dtpNextDate->date().toString("yyyy-MM-dd"), "yyyy-MM-dd");
                QDate endDate = startDate;

                QTime startTime = QTime::fromString(ui->dtpNextTime->time().toString("hh:mm:ss"), "hh:mm:ss");
                QTime endTime = startTime.addSecs(3600);

                QDateTime sdt = QDateTime(startDate, startTime);
                QDateTime edt = QDateTime(endDate, endTime);
                app->setDateTimes(sdt, edt);
                app->setSubject(ui->cboNextSubject->currentText());
                app->setPlace(ui->txtNextLocation->text());

                Publics::SaveNewAppointment(app);
            }
            this->accept();
        }
    } else {
        Publics::showError("Please select a customer.");
    }
}

#include "transactionview.h"
void ExtendedNewAction::on_cmdShowAgeing_clicked()
{
    QDialog *tdg = new QDialog(this, Qt::Dialog | Qt::Tool);
    TransactionView *vw = new TransactionView(tdg);
    vw->setCustomer(ui->cboCustomer->currentText());
    vw->setStartDate(QDate(2010, 1, 1));
    QBoxLayout *lay = new QBoxLayout(QBoxLayout::TopToBottom, tdg);
    lay->addWidget(vw);
    tdg->setLayout(lay);

    tdg->exec();
}

void ExtendedNewAction::on_cboCustomer_currentIndexChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    loadCustomerAgeing();
}

void ExtendedNewAction::on_cmdExit_clicked()
{
    this->reject();
    this->close();
}

void ExtendedNewAction::on_cboNextCalendar_editTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->cboNextSubject->setEditText(ui->cboNextCalendar->currentText());
}


