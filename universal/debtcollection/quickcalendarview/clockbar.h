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

#ifndef CLOCKBAR_H
#define CLOCKBAR_H

#include "calendaritem.h"
#include "quickcalendarstyle.h"

#include <QSize>

/**
* @class ClockBar
* @brief Класс для отображения списка часов от 0-00 до 23-00
*/ 
class ClockBar : public CalendarItem
{

public:
	///Конструктор
	ClockBar(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget);
};

#endif
