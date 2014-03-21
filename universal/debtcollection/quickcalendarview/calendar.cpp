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

#include "calendar.h"
#include <QtSql>
#include "publics.h"
/*!
	Сравнивает календари по значениям ключей
*/
	//Compares calendars by key values.
bool Calendar::operator==(const Calendar &other) const {
    if(this == &other) //если все поля равны, вернуть true
        return true;
    else if(other.myKey == myKey) //если ключи равны так же вернуть true, иначе false
        return true;
    else
        return false;
}

/*!
	Сравнивает календари по значениями ключей
*/
    //Compares calendars by key values.
bool Calendar::operator!=(const Calendar &other) const {
    return !(*this == other);
}

QList <Appointment *> Calendar::getAppointments(const QDate &date)
{
    QList <Appointment *> result;

    QListIterator <Appointment *> i(myAppointments);
    while(i.hasNext())
    {
        Appointment *app = i.next();

        if(app->startDate() == date ||
           app->endDate() == date ||
           (app->startDate() < date && app->endDate() > date))
        {
            result.append(app);
        }
    }

//    QSqlDatabase db = Publics::getDatabase();
//    if (db.isOpen()) {
//        QSqlQuery qu = db.exec("SELECT * FROM appointments WHERE StartDate = '"  + date.toString("yyyy-MM-dd") + "'");
//        while (qu.next()) {
//            QString calendarName = Publics::getDbValue(db, "SELECT * FROM appointment_types WHERE EntryID = '" + qu.record().value("AppointmentType").toString() + "'", "AppointmentTypeName");
//            if (calendarName == this->myName) {
//                Appointment *app = new Appointment();
//                //app->setKey(qu.record().value(0).toInt());
//                app->setCalendar(this);
//                app->setSubject("TEST");
//                app->setPlace("PLACE");
//                QDateTime st = QDateTime(date, QTime::fromString("11:15", "hh:mm"));
//                QDateTime et = QDateTime(date, QTime::fromString("11:36", "hh:mm"));
//                app->setStartDateTime(st);
//                app->setEndDateTime(et);

//                result.append(app);
//            }
//        }
//    }


    return result;
}
bool Calendar::insertAppointment(Appointment *appointment)
{
	/**
		Если у данной встречи не установлен ключ, то метод
		задает ключ по счетчику календаря и
		для встречи установливает данный календарь как родительский 
		(так как, одна и таже встреча не может быть в разных календарях).
	*/
    if(appointment->key() == 0)
    {

        appointment->setKey(myCounter);

        appointment->setCalendar(this);
        myCounter++;
    }
	
	/**
		Если встречи с заданным ключем еще нет, добавляет её в конец календаря.
	*/
    if(!myAppointments.contains(appointment))
    {
        myAppointments.append(appointment);
        return true;
    }
	/**
	*	@return Возращает false если встреча уже есть в календаре, иначе true
	*/
    return false;
}

bool Calendar::updateAppointment(const Appointment &appointment)
{
//    if(!ptrAppointments->contains(appointment))
//    {
//        ptrAppointments->replace(ptrAppointments->indexOf(appointment), appointment);
//        return true;
//    }

    return false;

}

bool Calendar::removeAppointment(Appointment *appointment)
{
    return myAppointments.removeOne(appointment);
}
