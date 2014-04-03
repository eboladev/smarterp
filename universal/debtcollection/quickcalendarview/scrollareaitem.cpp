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

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QGraphicsSceneWheelEvent>

#include "scrollareaitem.h"
#include "dayitem.h"

ScrollAreaItem::ScrollAreaItem(QGraphicsItem *parent, QGraphicsScene *scene) : 
    CalendarItem(parent, scene), myVertical(this, scene), myContent(this, scene), ptrItem(0)
{
    myContent.setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}


void ScrollAreaItem::setItem(CalendarItem *item)
{
	//Если задан элемент
    if(item != 0)
    {	//Устанавливает родительскм для этого элемент клиентскую область прокрутки
        item->setParentItem(&myContent);
		//Максимальное значения полоски прокрутки устанавливается равным высоте элемента
        myVertical.setMaximum(item->boundingRect().height());
    }
    ptrItem = item;
}

/**
* @brief Цвет фона области задается (127,127,127)
* @param painter - класс прорисовки
* @param option - опции прорисовки
*/
void ScrollAreaItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int left = 0;
    int top = 0;
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    painter->setBrush(QBrush(QColor(127, 127, 127)));
    painter->drawRect(left, top, width, height);
}

void ScrollAreaItem::onResize(const QSizeF &size, const QSizeF &oldSize)
{
    layoutChanged();
}

/**
* @brief Обрабатывает смену слоя
*/
void ScrollAreaItem::layoutChanged()
{
    //int left = 0;
    //int top = 0;
	//Получаем высоту и ширину полной области прорисовки
    qreal width = myBoundingRect.width();
    qreal height = myBoundingRect.height();

	//Получаем ширину области рисования для полоски прокрутки
    qreal verticalBar = myVertical.boundingRect().width();

    //Устанавливает размер области прокрутки для элементов 
    myContent.setSize(width - verticalBar, height);

	//Задает параметры полоски прокрутки
    myVertical.setPos(width - verticalBar, 0); //Устанавливаем позицию
    myVertical.setSize(verticalBar, height); //Ширина полоски задается шириной области рисования для неё

	//Если установлен элемент календаря для области прокрутки, то
	//максимальное значение полоски устанавливается высотой элемента
    if(ptrItem != 0)
    {
        myVertical.setMaximum(ptrItem->boundingRect().height());
    }

    //myVertical.layoutChanged();
}

void ScrollAreaItem::scrollTo(qreal value)
{
    myVertical.scrollTo(value);
}

/*!
	Используется только y, поскольку горизонтальная прокрутка не поддерживается.
*/
void ScrollAreaItem::ensureVisibility(qreal x, qreal y)
{
    myVertical.ensureVisibility(y);
}

qreal ScrollAreaItem::scrollBarWidth() const
{
    return myVertical.boundingRect().width();
}

void ScrollAreaItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
	///Изменяет значение полоски прокрутки на четверть изменения положения колесика
	///с обратным знаком(т.к. движение колесика вперед сооствествует подъему бегунка полоски прокрутки)
    myVertical.scrollBy(-event->delta() / 4);
	//??
    layoutChanged();
}
