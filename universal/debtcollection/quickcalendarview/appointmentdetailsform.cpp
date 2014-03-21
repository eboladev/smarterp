/*******************************************************************************

    Copyright (C) 2008 Jukka-Pekka Mдkelд.
    Contact: jpm@mehteenit.net

    This file is part of QuickCalendar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QuickCalendar.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <QtCore>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

#include "appointmentdetailsform.h"
#include "publics.h"
#include "ui_appointmentdetailsform.h"
/*!
    Constructor for AppointmentDetailsForm
*/
AppointmentDetailsForm::AppointmentDetailsForm(Appointment *appointment,
                                               QList <Calendar *> *calendars,
                                               QWidget *parent) :
    QWidget(parent), ui(new Ui::AppointmentDetailsForm), ptrAppointment(appointment)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose, true);

    QRegExp subjectRx("^.{3,45}$");
    ui->subjectEdit->setValidator(new QRegExpValidator(subjectRx, this));

    ptrCalendars = new QList <Calendar *>();

    // Create icons for calendar combobox.
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

            ui->calendarCombo->addItem(icon, cal->name(), cal->key());

            ptrCalendars->append(cal);

            if(appointment->calendar() != 0)
                if(cal == appointment->calendar())
                    ui->calendarCombo->setCurrentIndex(j);

            j++;
        }
    }

    ui->startDateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    ui->startDateEdit->setDate(appointment->startDate());
    ui->startTimeEdit->setTime(appointment->startTime());

    ui->endDateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    ui->endDateEdit->setDate(appointment->endDate());
    ui->endTimeEdit->setTime(appointment->endTime());

    ui->subjectEdit->setText(appointment->subject());
    ui->placeEdit->setText(appointment->place());
    ui->descriptionEdit->setPlainText(appointment->description());

    ui->chkCompleted->setChecked(appointment->isComplete);

    if(ptrAppointment->key() == 0)
        ui->deleteAppointmentButton->hide();

    connect(ui->startDateEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(startDateTimeChanged(const QDateTime &)));
    connect(ui->startTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(startDateTimeChanged(const QDateTime &)));
    connect(ui->endDateEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(endDateTimeChanged(const QDateTime &)));
    connect(ui->endTimeEdit, SIGNAL(dateTimeChanged(const QDateTime &)),
            this, SLOT(endDateTimeChanged(const QDateTime &)));

    connect(ui->saveChangesButton, SIGNAL(clicked()), this, SLOT(onSaveChanges()));
    connect(ui->discardChangesButton, SIGNAL(clicked()), this, SLOT(onDiscardChanges()));
    connect(ui->deleteAppointmentButton, SIGNAL(clicked()), this, SLOT(onDeleteAppointment()));

    connect(ui->subjectEdit, SIGNAL(returnPressed()), this, SLOT(onSaveChanges()));
    connect(ui->placeEdit, SIGNAL(returnPressed()), this, SLOT(onSaveChanges()));

    QSqlDatabase db = Publics::getDatabase();
    Publics::loadDbToComboBox(db, ui->cboCustomer, "SELECT CompanyName FROM customers", "CompanyName");
    QString custName = Publics::getDbValue(db, "SELECT CompanyName FROM customers WHERE CustomerID = '" + appointment->customerID() + "'", "CompanyName");


    for (int c = 0; c < ui->cboCustomer->count(); c++) {
        if (ui->cboCustomer->itemText(c) == custName)
            ui->cboCustomer->setCurrentIndex(c);
    }
}

void AppointmentDetailsForm::setCloseHidden(bool h)
{
    ui->deleteAppointmentButton->setHidden(h);
}

/*!
    If form data is valid saves changes.
*/
void AppointmentDetailsForm::onSaveChanges()
{
    // Validate subject
    QSqlDatabase db = Publics::getDatabase();
//    QString subject = ui->subjectEdit->text();
//    int pos = 0;
//    if(ui->subjectEdit->validator()->validate(subject, pos) != QValidator::Acceptable)
//    {
//        QMessageBox::warning(0, QObject::tr("Invalid data!"), QObject::tr("Subject must be 3-45 characters long!"));
//        return;
//    }

    QDateTime start(ui->startDateEdit->date(), ui->startTimeEdit->time());
    QDateTime end(ui->endDateEdit->date(), ui->endTimeEdit->time());

    ptrAppointment->setDateTimes(start, end);
    ptrAppointment->setSubject(ui->subjectEdit->text());
    ptrAppointment->setPlace(ui->placeEdit->text());
    ptrAppointment->setDescription(ui->descriptionEdit->toPlainText());
    ptrAppointment->isComplete = ui->chkCompleted->isChecked();
    QString custID = Publics::getDbValue(db, "SELECT CustomerID FROM customers WHERE CompanyName = '" +ui->cboCustomer->currentText() + "'", "CustomerID");
    ptrAppointment->setCustomerID(custID);

    if(ptrAppointment->key() == 0)
    {
        Calendar *cal = ptrCalendars->at(ui->calendarCombo->currentIndex());
        cal->insertAppointment(ptrAppointment);
        Publics::SaveNewAppointment(ptrAppointment);
    } else {
        Calendar *cal = ptrCalendars->at(ui->calendarCombo->currentIndex());
        ptrAppointment->setCalendar(cal);
        ptrAppointment->setCalendarKey(cal->key());
    }
    emit onClose(ptrAppointment);
    this->close();
}

/*!
    Discards all changes.
*/
void AppointmentDetailsForm::onDiscardChanges()
{
    this->close();
}

/*!
    Deletes appointment.
*/
void AppointmentDetailsForm::onDeleteAppointment()
{
    Calendar *cal = ptrAppointment->calendar();
    cal->removeAppointment(ptrAppointment);

    QSqlDatabase db = Publics::getDatabase();
    QSqlQuery qu = db.exec("UPDATE appointments SET Deleted = 'Yes' WHERE AppointmentID = '" + QString::number(ptrAppointment->key()) + "'");
    if (qu.lastError().isValid()) {
        Publics::showError(qu.lastError().text());
    }
    emit onClose(ptrAppointment);
    this->close();
}

/*!
    Event handler for start date and time changes.
*/
void AppointmentDetailsForm::startDateTimeChanged(const QDateTime &datetime)
{
    if (ui->startDateEdit->date() > ui->endDateEdit->date())
    {
        ui->endDateEdit->setDate(ui->startDateEdit->date());
    }

    if (ui->startDateEdit->date() == ui->endDateEdit->date() &&
            ui->startTimeEdit->time() > ui->endTimeEdit->time().addSecs(-3600))
    {
        if(ui->endTimeEdit->time() < QTime(23,0,0))
        {
            ui->endTimeEdit->setTime(ui->startTimeEdit->time().addSecs(3600));
        }else
        {
            ui->endTimeEdit->setTime(QTime(23,59,59));

            if(ui->startTimeEdit->time() > QTime(23,0,0))
                ui->startTimeEdit->setTime(QTime(23,0,0));
        }
    }
}

/*!
    Event handler for end date and time changes.
*/
void AppointmentDetailsForm::endDateTimeChanged(const QDateTime &datetime)
{
    if (ui->endDateEdit->date() < ui->startDateEdit->date())
    {
        ui->startDateEdit->setDate(ui->endDateEdit->date());
    }

    if ((ui->startDateEdit->date() == ui->endDateEdit->date() &&
         ui->endTimeEdit->time() < ui->startTimeEdit->time().addSecs(3600)) ||
            (ui->startDateEdit->date() == ui->endDateEdit->date() &&
             ui->startTimeEdit->time() == QTime(23,0,0) &&
             ui->endTimeEdit->time() < QTime(23,59,59)))
    {
        if(ui->startTimeEdit->time() >= QTime(1,0,0))
        {
            ui->startTimeEdit->setTime(ui->endTimeEdit->time().addSecs(-3600));
        }else
        {
            ui->startTimeEdit->setTime(QTime(0,0,0));

            if(ui->endTimeEdit->time() < QTime(1,0,0))
                ui->endTimeEdit->setTime(QTime(1,0,0));
        }
    }
}

/*!
    Event handler form close.
*/
//void AppointmentDetailsForm::closeEvent(QCloseEvent *event)
//{

//    event->accept();
//}
