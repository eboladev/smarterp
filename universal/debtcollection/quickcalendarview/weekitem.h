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

#ifndef WEEKITEM_H
#define WEEKITEM_H

#include <QGraphicsItemGroup>
#include <QFont>

#include "calendaritem.h"
#include "scrollareaitem.h"
#include "clockbar.h"

class QuickCalendarView;
class DayItem;

class WeekItem : public CalendarItem
{

public:
	WeekItem(QuickCalendarView *calendarView,
		 const QDate &date,
		 const QDate &end,
		 QGraphicsItem *parent = 0,
		 QGraphicsScene *scene = 0);
	~WeekItem() {}

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget);

	virtual void layoutChanged();
	virtual void dataChanged();

	bool hasDate(const QDate &date);
	int dayOfWeek(const QDate &date);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	QuickCalendarView *ptrCalendarView;

	CalendarItem *dayHeaderContainer;
	CalendarItem *dayContentContainer;

	CalendarItem *ptrScrollPane;

	ScrollAreaItem *ptrScrollArea;

	ClockBar *clockBar;

	QDate myDate;
	QDate myRangeStart;
	QDate myRangeEnd;

	QList <DayItem *> myDays;

	QFont myFont;

	friend class QuickCalendarView;
	friend class DayItem;
	friend class DayContentItem;
	friend class AppointmentItem;
};

#endif
