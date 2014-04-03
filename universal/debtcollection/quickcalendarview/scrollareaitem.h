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

#ifndef SCROLLAREAITEM_H
#define SCROLLAREAITEM_H

#include "calendaritem.h"
#include "scrollbar.h"

/**
 @class ScrollAreaItem
 @brief Класс, реализующий область прокрутки для элемента календаря
*/
class ScrollAreaItem : public CalendarItem
{

public:
	///Конструктор
	ScrollAreaItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	///Связывает элемент колендаря и область прокрутки
	void setItem(CalendarItem *item);

	///Метод прорисовки области прокрутки
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		   QWidget *widget);

	virtual void layoutChanged();

	///Установить новое значение для полоски прокрутки
	void scrollTo(qreal value);
	
	///Задает область видимости для полосы прокрутки
	void ensureVisibility(qreal x, qreal y);

	qreal scrollBarWidth() const; ///<Получить ширину полоски прокрутки

	virtual void onResize(const QSizeF &size, const QSizeF &oldSize);

	//    int length;
	//    int pos;

protected:
	///Обработчик колесика мыши для управления ползунком скроллинга
	void wheelEvent(QGraphicsSceneWheelEvent *event);
private:
	ScrollBar myVertical; ///<Вертикальная полоска прокрутки
	CalendarItem myContent; ///<Задает параметры области содержимого (размер области скроллинга без размера полосок прокрутки)
	CalendarItem *ptrItem; ///<Элемент календаря связанный с областью прокрутки

	friend class ScrollBar;
};

#endif
