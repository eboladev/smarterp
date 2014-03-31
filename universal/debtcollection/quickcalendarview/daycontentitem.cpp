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
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include "daycontentitem.h"
#include "appointmentitem.h"
#include "appointmentdetailsform.h"
#include "weekitem.h"
#include "dayitem.h"
#include "quickcalendarview.h"

/**
* @param dayItem -  указатель на DayItem.
* @param parent -  указатель на родителя.
* @param scene - указатель на сцену.
*/
DayContentItem::DayContentItem(DayItem *dayItem, QGraphicsItem *parent, QGraphicsScene *scene) : 
    CalendarItem(parent, scene), ptrDayItem(dayItem) //Вызываем конструктор родителя, инициализируем ptrDayItem
{
    myColumns = 1; 
    dragStart = dragEnd = 0;  //Начало выделенной области и конец 0
    dragSelection = false; //Мышью ничего не выбрано

    setHandlesChildEvents(true); //Объект будет обрабатывать события для всех его детей
    setFlag(QGraphicsItem::ItemIsSelectable); //Разрешаем выделение элементов
    setAcceptHoverEvents(true); //Объект будет захватывать hover events
	//Hover events are delivered when there is no current mouse grabber item.
	//Такие события формируются, когда нет текущего захваченного мышью элемента.
}

void DayContentItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int left = 0; //Отступ слева
    int width = (int)myBoundingRect.width(); //Запоминаем ширину
    int height = (int)myBoundingRect.height(); //и высоту области для рисования

    if(ptrDayItem->myDate.dayOfWeek() < 6) //Если день недели меньше 6го (будний день)
    {
        painter->setBrush(QBrush(QColor(255,255,233))); //задаем цвет кисти
        painter->drawRect(0,height/3,width,height/3); //Рисуем фоновый прямоугольник 8-00 15-00

        painter->setBrush(QBrush(QColor(233,233,233))); //Задаем цвет кисти
        painter->drawRect(0,0,width,height/3); //фоновый прямоугольник 0-00 до 7-00
        painter->drawRect(0,(height*2)/3,width,height/3); //16-00 - 23-00
    }else //Выходной день - аналогично буднему, но другим цветом
    {
        painter->setBrush(QBrush(QColor(225,225,203)));
        painter->drawRect(0,height/3,width,height/3);

        painter->setBrush(QBrush(QColor(203,203,203)));
        painter->drawRect(0,0,width,height/3);
        painter->drawRect(0,(height*2)/3,width,height/3);
    }

    painter->setPen(QPen(QColor(127,127,127))); //Задаем цвет пера
	/*Возможная ошибка: число 10 необходимо брать из поля 
	     ptrDayItem->ptrCalendarView->style()->quarterHeight;*/
    for(int i=0;i<23;i++)
    {
        painter->drawLine(left, i*10*4, left+width, i*10*4); //Рисуем 24 горизонтальные линии (границы часа)
    }

    painter->setPen(QPen(QColor(191,191,191))); //Задаем цвет пера

    for(int i=0;i<23;i++)
    {
         painter->drawLine(left, i*10*4 + 10 * 2, left+width, i*10*4 + 10 * 2);
		  //Рисуем 24 горизонтальные линии (границы получаса)
    }

    if(option->state & QStyle::State_MouseOver)
    {
    }

    // Selection
    if(dragSelection) //Если существует выбранная мышью область
    {
        painter->setPen(Qt::NoPen); //Убираем границы
        painter->setBrush(QBrush(QColor(0,63,255,127))); //Устанавливаем цвет
        painter->drawRect(0, dragStart, width, dragEnd); //Рисуем соотв. области прямоугольник
    }
}

void DayContentItem::dataChanged()
{
    qDeleteAll(childItems()); //Удалить дочерние элементы

    int minEndTime = 0; //Минимальное время окончания
    int currentColumn = 0; //Текущий элемент
    QVector<int> columns; //Вектор хранит номера четвертей часов, в которых оканчиваются встречи
	columns << 0; //Помещаем туда 0

    QListIterator <Appointment *> i(ptrDayItem->myAppointments); //Встречи
    while(i.hasNext()) //Идем по встречам
    {
        Appointment *appointment = i.next(); //Получаем объект встречи

		//Создаем объект для граф. отображения встречи
        AppointmentItem *item = new AppointmentItem(appointment, ptrDayItem, this);

        minEndTime = 24 * 4; //Установим минимальное время

		//Находим минимальное время окончания встречи во всех рядах
        for(int j=0;j<columns.size();j++)
        {
            if(columns[j] < minEndTime)
            {
                minEndTime = columns[j];
                currentColumn = j;
            }
        }
        
		///Если номер четверти часа начала встречи меньше минимального времени окончания
        if(appointment->startQuater(ptrDayItem->myDate) < minEndTime)
        {
            item->setColumn(columns.size());  //Установим элемент в последний ряд
            item->setColumnSpan(1); //Элемент перекрывает 1 ряд
            columns.append(appointment->endQuater(ptrDayItem->myDate)); 
			//Добавляем в вектор время четверти часа окончания встречи
        }else{

            int beginTime = appointment->startQuater(ptrDayItem->myDate); //Получим номер четверти часа начала встречи
            int columnSpan = 1; //Элемент перекрывает 1 ряд

            for(int j=0;j<columns.size();j++) //Идем по вектору
            {
                if(columns[j] <= beginTime) //Если время меньше времени начала
                {
                    int width = 1; //Ширина 1
                    for(int k=j+1;k<columns.size();k++) //Идем по оставшейся части массива
                    {
						//Считаем количество идущих подряд ячеек, у которых содержимое меньше или равно beginTime
                        if(columns[k] <= beginTime)
                        {
                            width++;
                        }else
                        {
                            break;
                        }
                    }

                    if(width > columnSpan) //Если ширина больше количества рядов, перекрываемых элементом
                    {
                        columnSpan = width; //Запомним число перекрываемых рядов
                        currentColumn = j; //и запомним текущий элемент
                    }
                }
            }

            item->setColumn(currentColumn); //Зададим ячейку
            item->setColumnSpan(columnSpan);// Зададим число перекрываемых рядов

			//Для всех элементов от текущего до текущего плюс промежуток
            for(int j=currentColumn;j<currentColumn+columnSpan;j++)
                columns[j] = appointment->endQuater(ptrDayItem->myDate); //Зададим значение, равное четверти окончания встречи
        }
    }

    myColumns = columns.size(); //Запомним количество рядов
}


void DayContentItem::layoutChanged()
{
    int left = 0; //Отступ слева
        //int top = 0;
    int width = (int)myBoundingRect.width(); //Запомним ширину области рисования
        //int height = myBoundingRect.height();

    int quarterHeight = 10; //Высота одной четверти часа

    int columnWidth = width / myColumns; //Вычисляем ширину 1го ряда

    QListIterator <QGraphicsItem *> j(childItems()); //Идем по элементам для отображения встречи
    while(j.hasNext())
    {
        AppointmentItem *item = (AppointmentItem *)j.next(); //Текущий элемент

        const Appointment *appointment = item->ptrAppointment; //Текущая встреча

		//Вычисляем положение элемента по вертикали
        int itemTop = quarterHeight * appointment->startQuater(ptrDayItem->myDate); 
		//Вычисляем высоту элемента
        int itemHeight = (quarterHeight * appointment->endQuater(ptrDayItem->myDate)) - itemTop;

        qDebug() << itemHeight;
        if (itemHeight < 80)
            itemHeight = 80;

        if(item->column() == 0){ //Если элемент находится в 0ом ряду
            item->setPos(left + (columnWidth * item->column()),itemTop); //Задаем позицию элемента
            item->setSize((width%myColumns) + (columnWidth*item->columnSpan()),itemHeight); //и его размер
        }else
        {//если не в нулевом ряду
            item->setPos(left + (width%myColumns) + (columnWidth * item->column()), itemTop);//Задаем позицию элемента
            item->setSize(columnWidth*item->columnSpan(),itemHeight);//и его размер
        }

        item->layoutChanged(); //Вызываем layoutChanged
    }
}

/**
* @param event - событие мыши в каркасе графического представления.
*/
void DayContentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos(); //Получаем позицию указателя

    QListIterator <QGraphicsItem *> j(childItems()); //Идем по элементам для отображения встречи
    while(j.hasNext())
    {
        AppointmentItem *item = (AppointmentItem *)j.next();
        if(item->sceneBoundingRect().contains(pos)) //Ищем по какой встречи пользователь кликнул
        {
            ptrDayItem->ptrCalendarView->showAppointmentForm(item->ptrAppointment); //Вызываем ее форму настройки
        }
    }
}

/**
* @param event - событие мыши в каркасе графического представления.
*/
void DayContentItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int y = (int)event->pos().y(); //Получаем позицию мыши
    dragStart = (int)event->pos().y() - y%20; //Координата начала выделения мышью
    dragEnd = 0; //Окончание на 0
    dragSelection = true; //Флаг того, что существует выбранная мышью область
}

/**
* @param event - событие мыши в каркасе графического представления.
*/
void DayContentItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(dragSelection) //Если выделение идет
    {
        int y = (int)event->pos().y(); //Получаем положение мыши
        dragEnd = y + 20 - y%20 - dragStart; //Вычисляем координату окончания выделения

        //ptrDayItem->ptrWeekItem->myScrollArea.ensureVisibility(0, event->pos().y());

        update(); //Обновляем виджет
    }
}

/**
* @param event - событие мыши в каркасе графического представления.
*/
void DayContentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(dragSelection && dragEnd != 0) //Если было выделение мышью
    {
        int startHour = dragStart / 40; //Вычислим час начала
        int startMinute = 0; //Минуты начала
        if(dragStart%40 > 0) //Если на 40 не делится нацело
            startMinute = 30; //Установим 30 минут
        QDateTime start(ptrDayItem->myDate, QTime(startHour, startMinute, 0)); //Сформируем объект дата-время

        int endHour = (dragStart + dragEnd) / 40; //Вычислим час окончания встречи
        int endMinute = 0; // и минуты окончания
        if((dragStart + dragEnd)%40 > 0)
            endMinute = 30;
        if(endHour == 24) //Если час окончания равен 24
        {
            endHour = 23; //Установим 23 часа
            endMinute = 59; //59 минут
        }
        QDateTime end(ptrDayItem->myDate, QTime(endHour, endMinute, 0)); //Сформируем объект дата-время

        Appointment *appointment = new Appointment(); //Создадим новое событие

        if(startHour < endHour) //Если время начала меньше времени окончания
            appointment->setDateTimes(start, end); //Установим время
        else
            appointment->setDateTimes(end, start); //Иначе установим время наоборот

        ptrDayItem->ptrCalendarView->showAppointmentForm(appointment); //Отобразим форму настройки встречи

        dragSelection = false; //Выделения больше нет
        update(); //Обновим виджет
    }
}
