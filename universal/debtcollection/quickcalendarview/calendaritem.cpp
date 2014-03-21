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
#include "calendaritem.h"

/**
* @param parent -  указатель на родителя.
* @param scene - указатель на сцену.
*/
CalendarItem::CalendarItem(QGraphicsItem *parent,
                           QGraphicsScene *scene) :
    QGraphicsItem(parent) //Вызов конструктора базового класса
{
}

/**
* @return контейнер операций рисования.
*/
QPainterPath CalendarItem::shape () const
{
    QPainterPath result; //Создаем контейнер операций рисования
    result.addRect(myBoundingRect); //Добавляем в него прямоугольник
    return result; //Возвращаем результат
}

/**
* @param painter - указатель на класс рисования QPainter.
* @param option - указатель на класс, содержащий параметры рисования.
* @param widget - указатель на виджет.
*/
void CalendarItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(QColor(0,0,0,128));
//    painter->drawRect(0,0,myBoundingRect.width(),myBoundingRect.height());
}

/**
* @return размер области для рисования.
*/
QRectF CalendarItem::boundingRect() const
{
    return myBoundingRect; //Вернуть размер
}
/**
* @param size - устанавливаемый размер.
*/
void CalendarItem::setSize(const QSize &size)
{
        if(size.width() != myBoundingRect.width() ||
           size.height() != myBoundingRect.height()) //если новый размер отличен от текущего
    {
        prepareGeometryChange(); //Подготавливаем элемент для смены геометрии.
        QSizeF old = myBoundingRect.size(); //Запоминаем старый размер
        myBoundingRect.setWidth(size.width()); //устанавливаем новую ширину
        myBoundingRect.setHeight(size.height()); //и высоту
        onResize(size, old); //Вызваем обработчик перерисовки
        update(); //перерисовка области элемента
    }
}

/**
* @param width - устанавливаемая ширина.
* @param height - устанавливаемая высота.
*/
void CalendarItem::setSize(qreal width, qreal height)
{
    if(width != myBoundingRect.width() || height != myBoundingRect.height())
    {
        prepareGeometryChange(); //Подготавливаем элемент для смены геометрии.
        QSizeF old = myBoundingRect.size();//Запоминаем старый размер
        QSizeF size(width, height); //Новый размер
        myBoundingRect.setWidth(width); //устанавливаем новую ширину
        myBoundingRect.setHeight(height); //и высоту
        onResize(size, old); //Взываем обработчик перерисовки
        update(); //перерисовка области элемента
    }
}

/**
* Реализация по умолчанию не требуется.
* @param size - новый размер.
* @param oldSize - старый размер.
*/
void CalendarItem::onResize(const QSizeF &size, const QSizeF &oldSize)
{
}

/*!
    Реализация по умолчанию не требуется.
*/
void CalendarItem::layoutChanged()
{
}

/*!
    Реализация по умолчанию не требуется.
*/
void CalendarItem::dataChanged()
{
}
