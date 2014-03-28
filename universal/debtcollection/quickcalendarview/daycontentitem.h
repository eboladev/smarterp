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

#ifndef DAYCONTENTITEM_H
#define DAYCONTENTITEM_H

#include "calendaritem.h"
 
class DayItem;

/**
* @class DayContentItem
* @brief Класс для отображения содержимого дня недели
*/ 
class DayContentItem : public CalendarItem
{

public:
	///Конструктор
    DayContentItem(DayItem *dayItem, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    virtual void layoutChanged();
    virtual void dataChanged();

protected:
	///Обработчик события двойного клика мышью
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    ///Обработчик события нажатия клавиши мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик события перемещения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик события отпускания клавиши мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    DayItem *ptrDayItem; ///<Указатель на DayItem 

    int myColumns; //< Число рядов

    int dragStart; //<Начало выделенной мышью области
    int dragEnd; //<Окончание выделенной мышью области

    bool dragSelection; //<Флаг, показывающий выделена ли мышью какая-либо область
};

#endif
