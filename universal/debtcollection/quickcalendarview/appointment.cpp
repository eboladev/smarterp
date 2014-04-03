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

#include "appointment.h"

/**
* @param startDateTime - момент начала.
* @param endDateTime - момент окончания.
*/
void Appointment::setDateTimes(const QDateTime &startDateTime, const QDateTime &endDateTime)
{
	if(startDateTime <= endDateTime) //Если момент начала раньше момента окончания
	{
		myStartDateTime = startDateTime; //установить момент начала
		myEndDateTime = endDateTime; //установить момент окончания
	}
	else //иначе
	{
		myEndDateTime = myStartDateTime = startDateTime; //Установить момент начала и окончания равными
	}
}
/**
* @param startTime - время начала.
* @param endTime - время окончания.
*/
void Appointment::setTimes(const QTime &startTime, const QTime &endTime)
{
	if(startTime <= endTime) //Если время начала раньше времени окончания
	{
		myStartDateTime.setTime(startTime); //Установить время начала
		myEndDateTime.setTime(endTime); //Установить время окончания
	}
	else //Иначе
	{
		myStartDateTime.setTime(startTime); //То же самое!!!
		myEndDateTime.setTime(endTime);
	}
}

/**
* @brief Устанавливает дату и время начала встречи.
* @param startDateTime - момент начала встречи.
*/
#include "publics.h"
void Appointment::setCustomerID(const QString &customerID)
{

	myCustomer = customerID;
	customerName = Publics::getDbValue(Publics::getDatabase(), "SELECT CompanyName FROM customers WHERE CustomerID = '" + myCustomer + "'", "CompanyName");
}

void Appointment::setStartDateTime(const QDateTime &startDateTime)
{
	if(startDateTime <= myEndDateTime) //Если момент начала встречи раньше момента ее окончания
	{
		myStartDateTime = startDateTime; //Установить момент начала встречи
	}else //иначе
	{
		myStartDateTime = myEndDateTime; //Установить момент начала встречи равный моменту ее окончания
	}
}

/**
* @brief Устанавливает дату и время окончания встречи.
* @param endDateTime - момент окончания встречи.
*/
void Appointment::setEndDateTime(const QDateTime &endDateTime)
{
	if(endDateTime >= myStartDateTime) //Если момент начала встречи раньше момента ее окончания
	{
		myEndDateTime = endDateTime; //Установить момент конца встречи
	}else //Иначе
	{
		myEndDateTime = myStartDateTime; //Установить момент окончания равный моменту начала встречи
	}
}

/**
	@brief Если date равна дате начала встречи, метод вернет номер четверти часа, в которой начнется встреча.
    Если date меньше чем дата окончания встречи, функция вернет 0.
	Иначе -1.
*/
int Appointment::startQuater(const QDate &date) const
{
	QTime time = myStartDateTime.time(); //Запомним время начала

	if(date == myStartDateTime.date()) //Если date равна дате начала
		return ((time.hour() * 60) + time.minute()) / 15; //Вернем количество четвертей
	else if(date <= myEndDateTime.date()) //Иначе, если date меньше даты окончания
		return 0; //вернем 0
	else
		return -1; //Иначе вернем -1
}

/**
	@brief Если date равна дате начала встречи, метод вернет номер четверти часа, в которой начнется встреча.
	Если date меньше чем дата окончания встречи, функция вернет 0.
	Иначе -1.
*/
int Appointment::endQuater(const QDate &date) const
{
	QTime time = myEndDateTime.time(); ////Запомним время окончания

	if(date == myEndDateTime.date()) //Если date равна дате окончания
		return ((time.hour() * 60) + time.minute()) / 15; //Вернем количество четвертей
	else if(myEndDateTime.date() > date) //Иначе, если date меньше даты окончания
		return (24 * 60) / 15; //Вернем количество четвертей часа в сутках
	else
		return -1; //Иначе -1.
}


bool Appointment::before(Appointment *app1, Appointment *app2)
{
	return app1->startDateTime() < app2->startDateTime(); //Сравниваем время начала встреч
}

/**
	@brief Сравнивает встречи по ключу.
*/
bool Appointment::operator==(const Appointment &other) const {
	if(this == &other) //сравниваем адреса
		return true;
	else if(other.myKey == myKey) //иначе сравниваем ключи
		return true;
	else
		return false;
}

/**
	@brief Сравнивает встречи по ключу.
*/
bool Appointment::operator!=(const Appointment &other) const {
	return !(*this == other); //Инверсия равенства
}

/**
	@brief Сравнивает встречи по времени их начала.
*/
bool Appointment::operator<(const Appointment &other) const {
	if(this == &other) //Сравниваем указатели
		return false;
	else if(other.myStartDateTime > myStartDateTime) //Сравниваем время начала встреч
		return true;
	else
		return false;
}

