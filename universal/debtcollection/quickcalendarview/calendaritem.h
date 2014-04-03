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

#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QSizeF>



/**
* @class CalendarItem
* @brief Базовый класс для всех графических элементов календаря.
*/ 
class CalendarItem : public QGraphicsItem
{

public:
	///Конструктор
	CalendarItem(QGraphicsItem *parent = 0,
		     QGraphicsScene *scene = 0);

	///Метод прорисовки графического элемента календаря.
	virtual void paint(QPainter *painter,
			   const QStyleOptionGraphicsItem *option,
			   QWidget *widget);

	///Возвращает изображение графического элемента.
	virtual QPainterPath shape () const;

	///Вернет размер области для рисования
	QRectF boundingRect() const;

	///Устнаваливает размер области для рисования
	void setSize(const QSize &size);
	///Устнаваливает размер области для рисования
	void setSize(qreal width, qreal height);

	///Обработчик изменения размера
	virtual void onResize(const QSizeF &size, const QSizeF &oldSize);

	///Обработчик изменения layout
	virtual void layoutChanged();
	///Обработчик изменения даты
	virtual void dataChanged();

protected:
	QRectF myBoundingRect; ///<Размер области рисования
};

#endif
