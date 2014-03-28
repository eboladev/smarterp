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

#ifndef APPOINTMENTDETAILSFORM_H
#define APPOINTMENTDETAILSFORM_H

#include <QList>
#include <QWidget>
 
#include "appointment.h"
#include "calendar.h"
//#include "ui_appointmentdetailsform.h"

/*!
    \class AppointmentDetailsForm
    \brief Form to edit details of appointments.
*/



namespace Ui {
    class AppointmentDetailsForm;
}

class AppointmentDetailsForm : public QWidget
{
    Q_OBJECT

public:
    AppointmentDetailsForm(Appointment *appointment,
                           QList <Calendar *> *calendars,
                           QWidget *parent = 0);
    void setCloseHidden(bool h);
signals:
    void onClose(Appointment *appointment);

private slots:
    void onSaveChanges();
    void onDiscardChanges();
    void onDeleteAppointment();
    void startDateTimeChanged(const QDateTime &datetime);
    void endDateTimeChanged(const QDateTime &datetime);

protected:
    //virtual void closeEvent(QCloseEvent *event);

private:
    Ui::AppointmentDetailsForm *ui;
    Appointment *ptrAppointment;
    QList <Calendar *> *ptrCalendars;
};

#endif
