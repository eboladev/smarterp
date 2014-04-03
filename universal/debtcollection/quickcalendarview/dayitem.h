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

#ifndef DAYITEM_H
#define DAYITEM_H

#include <QBrush>
#include <QDate>
#include <QLinearGradient>
#include <QPen>
#include <QFont>
#include <QPixmap>

#include "calendaritem.h"
#include "daycontentitem.h"
#include "appointment.h"

class QuickCalendarView;

/**
 @class DayItem
 @brief Класс для графического отображения информации о дне недели
*/
class DayItem : public CalendarItem
{

public:
	/**
	@brief Конструктор элемента отображения дня недели
	@param calendar Родительский календарь для этого дня
	@param date Дата, которой принадлежит день
	@param parent Родильский графический элемент
	@param scene Сцена для графического отображения
	*/
	DayItem(QuickCalendarView *calendar,
		const QDate &date,
		QGraphicsItem *parent = 0,
		QGraphicsScene *scene = 0);
	
	/**
	@brief Установка информации даты для дня
	*/
	void setDate(const QDate &date);
	//void setWeekItem(
	/**
    @brief Метод прорисовки элемента дня
    */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget);

	//Наследуемые методы обработки изменения родительского слоя и данных
	virtual void layoutChanged();
	virtual void dataChanged();


	bool isOutOfRange() const { return amIOutOfRange; }
	void setOutOfRange(bool outOfRange) { amIOutOfRange = outOfRange; }

protected:
	///Обработчик нажатия мыши на элементе, не имеет реализации
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик перемещния мыши по элементу, не имеет реализации
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик отпускания мыши на элементе
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
	bool amIOutOfRange;

	QuickCalendarView *ptrCalendarView;
	QDate myDate; ///<Отображаемая дата

	DayContentItem *ptrContentItem;
	QBrush myBrush; ///
	QLinearGradient myGradient;
	QPen myPen;
	QFont myFont;

	QString myCaption;
	int myAlign;

	QList<Appointment *> myAppointments;

	QPixmap myClockIcon;

	friend class MonthItem;
	friend class WeekItem;
	friend class DayContentItem;
	friend class AppointmentItem;
};

#endif
