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

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "calendaritem.h"

class ScrollAreaItem;

/**
* @class ScrollBar
* @brief Класс, реализующий полосу прокрутки
*/
class ScrollBar : public CalendarItem
{
public:
	///Конструктор
    ScrollBar(ScrollAreaItem *scrollArea = 0, QGraphicsScene *scene = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);

    virtual void layoutChanged();

	///Вернет значение, соответствующее текущему положению ползунка
    qreal getValue() const;
	///Установит ползунок в положение, соответствующее value
    void scrollTo(qreal value);
    void scrollBy(qreal scrollBy);
    //void scrollBy(qreal sсrollBy);

    void setMinimum(qreal min);
	///Устанавливает значение, соответствующее нижнему положению ползунка
    void setMaximum(qreal max);

	///Действия при изменении размера
    virtual void onResize(const QSizeF &size, const QSizeF &oldSize);

    void ensureVisibility(qreal y); ///<Обеспечивает видимость

    int orientation; ///<Ориентация (не используется)

protected:
	///Обработчик события нажатия кнопки мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик события перемещения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	///Обработчик события отпускания кнопки мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal myMin; ///<Максимальное значение
    qreal myMax; ///<Минимальное значение
    qreal myValue; ///<Текущее значение
    qreal myFactor; ///<Масштаб

    qreal sliderMax; ///<Максимальное положение ползунка
    qreal sliderPos; ///<Текущее положение ползунка
    qreal sliderHeight; ///<Высота (размер) ползунка

    int pressedControl; ///<Флаг нажатия кнопки мыши

    ScrollAreaItem *ptrArea; ///<Прокручиваемая область
    //ScrollHandle myHandle;
};

#endif
