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

#ifndef APPOINTMENTITEM_H
#define APPOINTMENTITEM_H

#include <QColor>
#include <QFont>
#include <QString>

#include "appointment.h"
#include "calendaritem.h"
#include "dayitem.h"

/**
* @class AppointmentItem
* @brief Класс для графического представления информации о встречах
*/ 

class AppointmentItem : public CalendarItem
{

public:
	///Конструктор
	AppointmentItem(Appointment *appointment,
			DayItem *dayItem,
			QGraphicsItem *parent = 0,
			QGraphicsScene *scene = 0);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget);

	/**
    *	@brief Метод вернет номер ряда, в котором расположен элемент.
    *	@return номер ряда, в котором расположен элемент.
    */
	int column() const { return myColumn; }
	/**
    *	@brief Метод установит номер ряда, в котором расположен элемент.
    *	@param column - номер ряда.
    */
	void setColumn(int column) { myColumn = column; }

	/**
    *	@brief Метод вернет количество рядов, перекрываемых элементом.
    *	@return количество рядов, перекрываемых элементом.
    */
	int columnSpan() const { return myColumnSpan; }
	/**
    *	@brief Метод установит количество рядов, перекрываемых элементом.
    *	@param columnSpan - количество рядов, перекрываемых элементом.
    */
	void setColumnSpan(int columnSpan) { myColumnSpan = columnSpan; }

	void layoutChanged();

protected:
	///Обработчик события двойного клика мышью
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	Appointment *ptrAppointment; ///<Указатель на встречу
	DayItem *ptrDayItem; ///<Указатель на день
	QColor myColor; ///<Цвет элемента
	QFont myFont; ///<Шрифт текста на элементе
	QString mySubject; ///<Субъект встречи
	QString myCustomer;

	int myColumn; ///<Ряд, в котором расположен элемент
	int myColumnSpan; ///<Количество рядов, перекрываемых элементом

	friend class DayContentItem;
};


#endif
