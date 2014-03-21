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
#include <QGraphicsSceneMouseEvent>
#include "scrollbar.h"
#include "scrollareaitem.h"

/**
* @param scrollArea -  указатель на область, которой принадлежит полоса прокрутки.
* @param scene - указатель на сцену.
*/
ScrollBar::ScrollBar(ScrollAreaItem *scrollArea, QGraphicsScene *scene) : 
    CalendarItem(scrollArea, scene), ptrArea(scrollArea)
{
    myMin = 0.0; //Устанавливаем мин. значение
    myMax = 0.0; //макс. значение
    myValue = 0.0; //текущее значение
    myFactor = 1.0; //Масштаб

    sliderPos = 0; //позиция ползунка
    sliderMax = 0; //макс. позиция ползунка
    pressedControl = 0; //флаг нажатия ползунка

    myBoundingRect.adjust(0,0,16,16); //задаем область рисования
}

void ScrollBar::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int width = (int)myBoundingRect.width(); //Запоминаем ширину
    int height = (int)myBoundingRect.height(); //Запоминаем высоту

    painter->setPen(Qt::NoPen); //Устанавливаем стиль пера
    painter->setBrush(QBrush(QColor(161,161,129))); //Устанавливаем цвет кисти
    painter->drawRect(0,height/3,width,height/3); //Рисуем прямоугольник

    painter->setBrush(QBrush(QColor(191,191,191))); //Устанавливаем цвет кисти
    painter->drawRect(0,0,width,height/3); //Рисуем прямоугольник
    painter->drawRect(0,(height*2)/3,width,height/3); //Рисуем прямоугольник

    painter->setPen(QPen(QColor(63,63,63))); //Устанавливаем стиль пера
    painter->setBrush(QBrush(QColor(255,255,255,127))); //Устанавливаем цвет кисти
    painter->drawRect(0, sliderPos, width, sliderHeight); //Рисуем прямоугольник (ползунок)
}

void ScrollBar::layoutChanged()
{
    qreal height = myBoundingRect.height(); //Запоминаем высоту

    sliderHeight = height * myFactor;  //Изменяем высоту ползунка
    sliderPos = myValue * myFactor; //и его положение в соответствии с масштабом

    ptrArea->ptrItem->setPos(0, -myValue); //задаем позицию прокручиваемой области

    ptrArea->update(); //и обновляем ее
}

/**
* @param size -  новый размер.
* @param oldSize - старый размер.
*/
void ScrollBar::onResize(const QSizeF &size, const QSizeF &oldSize)
{
    qreal posFactor = 0; //новый масштаб

    if(oldSize.height() != 0) //если старый размер не 0.
        posFactor = size.height() / oldSize.height(); //Считаем отношение новой высоты к старой

    if(posFactor != 1) //Если масштаб не 1
    {
        if(myMax != 0) //Если макс значения не 0
            myFactor = size.height() / myMax; //Считаем новый масштаб
        else
            myFactor = 0; //Иначе 0

        if(myFactor > 1) //если масштаб больше 1
            scrollTo(0); //прокручиваем к 0
        else
            scrollTo(posFactor * myValue); //иначе к новому значению
    }
}

/**
* @param min -  новое минимальное значение.
*/
void ScrollBar::setMinimum(const qreal min)
{
    if(min != myMin) //Если новое значение не равно текущему
    {
        myMin = min; //Установим новое значение
        layoutChanged(); //изменить положение ползунка и прокрутить область
    }
}

/**
* @param min -  новое максимальное значение.
*/
void ScrollBar::setMaximum(const qreal max)
{
    if(max != myMax) //Если новое значение не равно текущему
    {
        myMax = max; //Установим новое значение

        if(myMax != 0) //если значение не 0
            myFactor = myBoundingRect.height() / myMax; //Считаем масштаб
        else
            myFactor = 0; //Иначе масштаб = 0

        if(myFactor >= 1) //если масштаб больше 1
            myValue = 0; //Установим значение 0

        layoutChanged(); //изменить положение ползунка и прокрутить область
    }
}

/**
* @return значение, соответстующее текущему положению ползунка.
*/
qreal ScrollBar::getValue() const
{
    return myValue; //вернуть значение
}
/**
* @param value -  новое значение.
*/
void ScrollBar::scrollTo(qreal value)
{
    if(value != myValue) //если новое значение не равно текущему
    {
        if(myFactor > 1) //Если масштаб больше 1
            myValue = 0; //Установим новое значение на 0
        else
        {
            if(value < myMin) //Если новое значение меньше минимального
                myValue = myMin; //установим минимальное
            else if(value > myMax - myBoundingRect.height()) //если больше максимального
                myValue = myMax - myBoundingRect.height(); //установим максимальное
            else 
                myValue = value; //иначе установим заданное
        }

        layoutChanged();//изменить положение ползунка и прокрутить область
    }
}
/**
* @param scrollBy -  разница между новым и старым значением.
*/
void ScrollBar::scrollBy(qreal scrollBy)
{
    if(myFactor < 1) //если масштаб меньше 1
        scrollTo(myValue + scrollBy); //прокрутим полосу к новому значению
}
/**
* @param y - значение.
*/
void ScrollBar::ensureVisibility(qreal y)
{
    if(y > myValue + myBoundingRect.height()) //если у больше тек. значения и высоты области прорисовки
    {
        scrollBy(10); //прокрутим на 10
    }else if(y < myValue) //Иначе если у меньше тек. значения
    {
        scrollBy(-10); //прокрутим на -10
    }
}
/**
* @param event - событие мыши в каркасе графического представления.
*/
void ScrollBar::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
    if (event->button() != Qt::LeftButton) { //если нажате не левая кнопка мыши
        event->ignore(); //игнорируем событие
        return;
    }

	//если мышь нажата не над ползунком
    if(event->pos().y() < sliderPos || event->pos().y() > sliderPos + sliderHeight)
        return; //выходим

    pressedControl = 1; //устанавливаем флаг нажатия мыши
    setCursor(Qt::ClosedHandCursor); //меняем курсор
 }
/**
* @param event - событие мыши в каркасе графического представления.
*/
void ScrollBar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(pressedControl == 1){ ///Если нажата левая кнопка
        if(myFactor != 0) //и масштаб не 0
            scrollBy((event->pos().y() - event->lastPos().y()) / myFactor); //Прокручиваем курсор
	}
}
/**
* @param event - событие мыши в каркасе графического представления.
*/
void ScrollBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressedControl = 0; //Сбрасываем флаг нажатия мыши
    setCursor(Qt::ArrowCursor); //Возвращаем стандартный курсор
}

