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

#include <QtCore>
#include <QtGui>

#include "appointmentdetailsform.h"
#include "appointmentitem.h"
#include "calendar.h"
#include "weekitem.h"
#include "quickcalendarview.h"


AppointmentItem::AppointmentItem(Appointment *appointment,
                                 DayItem *dayItem,
                                 QGraphicsItem *parent,
                                 QGraphicsScene *scene) :
    CalendarItem(parent, scene),
    ptrAppointment(appointment),    //Инициализируем поля
    ptrDayItem(dayItem),
    myFont("Verdana", 9, QFont::Bold)
{
    myColumn = 1; //По умолчанию элемент расположим в 1ом ряду
    myColumnSpan = 1; //Перекрывает 1 ряд

    setFlag(QGraphicsItem::ItemIsSelectable); //Разрешить выделение элемента
}

void AppointmentItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(myFont); //Установим шрифт

    painter->setPen(QPen(myColor)); //Цвет пера
    QColor color = myColor; //Запомним цвет пера
    if (ptrAppointment->isComplete) {
        myColor = QColor(191, 191, 191);
    }
    color.setAlpha(159); //Установим альфа-составляющую
    painter->setBrush(QBrush(color)); //Установим полученный цвет кисти
    painter->drawRoundedRect(myBoundingRect, 10, 10); //Рисуем прямоугольник


    painter->setPen(QPen(QColor(0,0,0)));
    qDebug() << "Drawing appointment " << ptrAppointment->key() << " for " << ptrAppointment->customerName << " on canvas";

    painter->drawText(myBoundingRect.adjusted(3,3,0,0),
                      Qt::AlignLeft | Qt::TextWordWrap,
                      myCustomer + "\n--\n" + mySubject);
}


void AppointmentItem::layoutChanged()
{
    myColor = ptrAppointment->calendar()->color(); //Запомним цвет календаря
    mySubject = ptrAppointment->subject(); //Запомним субъект встречи
    myCustomer = ptrAppointment->customerName;
}

/**
* @param event - событие мыши в каркасе графического представления.
*/
void AppointmentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    ptrDayItem->ptrCalendarView->showAppointmentForm(ptrAppointment); //Отобразим форму настройки встречи
}
