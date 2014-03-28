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
#include "appointmentdetailsform.h"
#include "quickcalendarview.h"
#include "dayitem.h"
#include "weekdayheaderitem.h"

QuickCalendarView::QuickCalendarView(QWidget *parent) :
    QGraphicsView(new QGraphicsScene(), parent)
{
    ptrStyle = new QuickCalendarStyle(); //Класс для хранения информации о внешнем виде календаря
    myDisplayMode = DisplayFullWeeks; //Устанавливаем способ отображения

    ptrContentPane = new CalendarItem(); //Создаем панель для содержимого
    scene()->addItem(ptrContentPane); //добавляем ее к сцене

    ptrHeader = new CalendarItem(); //создаем панель выбора месяца и года
    
    scene()->addItem(ptrHeader); //добавляем ее к сцене
    scene()->setBackgroundBrush(QColor(127, 127, 127)); //Задаем цвет фона граф. сцены

    for(int i=1;i<=7;i++)
    {
        WeekDayHeaderItem *item = new WeekDayHeaderItem(this, i, ptrHeader);
        //Создаем заголовки 7ми дней недели
    }

    myExpandedDayOfWeek = 0; //Все дни недели свернуты
    myExpandedWeekItem = 0; //Развернутая неделя

    myExpandedDate = QDate(0,0,0); //Развернутая дата

    myWeekCount = 0;

    ptrCalendars = new QList <Calendar *>(); //Создаем список календарей

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Отключаем горизонтальную и
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //вертик. прокрутку
    setFrameShape(QFrame::NoFrame);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //Будет перерисован ограничивающий прямоугольник всех изменений в области просмотра.
}

/**
*	@param mode способ отображения.
*/
void QuickCalendarView::setDisplayMode(DisplayMode mode)
{
    if(mode != myDisplayMode) //Если новый режим не равен старому
    {
        myDisplayMode = mode; //установить способ отображения
        setRange(myRangeStart, myRangeEnd); //Установить диапазон
    }
}

/**
*	@param start - дата начала отображения.
*	@param end - дата окончания отображения.
*/
void QuickCalendarView::setRange(const QDate &start,
                                 const QDate &end)
{
    collapseAll(); //Свернуть все элементы
    //qDeleteAll(myWeeks);
    if(myWeeks.count() > 0) //если количество недель не 0
    {
        qDeleteAll(myWeeks); //Удалить все недели
        myWeeks.clear(); //Очистить список недель
    }

    myRangeStart = start; //Начало отображения
    myRangeEnd = end; //Конец

    if(myRangeEnd < myRangeStart) //Если начало отображения позже конца
        myRangeEnd = myRangeStart; //Конец отображения равен началу

    if(myRangeStart.daysTo(myRangeEnd) > (7*10)-1) //Если разница между временем начала и конца больше 10 недель
        myRangeEnd = myRangeStart.addDays((7*10)-1); //Установить разницу в 69 дней

    if(myDisplayMode == DisplayFullWeeks) //Если отображаем полные недели
    {
        myStartDate = myRangeStart.addDays(-(myRangeStart.dayOfWeek() - 1)); //Устанавливаем даты начала и конца
        myEndDate = myRangeEnd.addDays(7-myRangeEnd.dayOfWeek()); //как ближайшие начало и конец недели

        myWeekCount = (myStartDate.daysTo(myEndDate) + 1) / 7; //вычисляем количество отображаемых недель

        for(int i=0;i<myWeekCount;i++) //Создаем недели
        {
            WeekItem *week;
            if(i==0)
                week = new WeekItem(this, myRangeStart, myRangeEnd, ptrContentPane);
            else
                week = new WeekItem(this, myStartDate.addDays(i*7), myRangeEnd, ptrContentPane);

            myWeeks.append(week); //Добавляем недели в массив
        }
        dataChanged(); //Измеяем даты

        if(myWeekCount == 1) //если отображается 1 неделя
            expandWeek(myWeeks.at(0)); //развернуть ее
        else
            layoutChanged(); //иначе изменить выравнивание

    }else if(myDisplayMode == DisplayOnlyRange) //Если отображаем диапазон
    {
        myStartDate = myRangeStart; //Установить дату начала

        if(myRangeStart.daysTo(myRangeEnd) > 13) //если разница между датой начала отображения и датой конца >13
            myRangeEnd = myRangeStart.addDays(13); //Установить разницу в 13 дней

        myEndDate = myRangeEnd; //Установить окончания диапазона

        WeekItem *week = new WeekItem(this, myStartDate, myEndDate, ptrContentPane); //Создаем неделю
        myWeeks.append(week); //добавляем ее в массив

        myWeekCount = 1; //количество неделей 1
        dataChanged();  //Изменить дату
        expandWeek(week); //развернуть неделю
    }
}

/**
*	@param year - устанавливаемый год.
*	@param month - устанавливаемый месяц.
*/
void QuickCalendarView::setMonth(int year, int month)
{
    QDate start(year, month, 1); //начальная дата
    QDate end = start.addDays(start.daysInMonth() - 1); //конечная дата

    setRange(start, end); //Установить диапазон
}

/**
*	@param calendars - указатель на устанавливаемый список календарей.
*/
void QuickCalendarView::setCalendars(QList <Calendar *> *calendars)
{
    ptrCalendars = calendars; //запомнить календари
}

/**
*	@param date - разворачиваемая дата.
*/
void QuickCalendarView::expandDate(const QDate &date)
{
    bool weekChanged = false; //флаг изменения недели

    if(date != myExpandedDate) //если дата не равна уже развернутой
    {
        QListIterator <WeekItem *> i(myWeeks); //Идем по неделям
        while(i.hasNext())
        {
            WeekItem *week = i.next();

            int dayOfWeek = week->dayOfWeek(date); //Получаем день недели
            if(dayOfWeek >= 0) //если день недели больше 0
            {
                if(myExpandedWeekItem != week) //развернутая неделя не равна текущей
                    weekChanged = true; //установим флаг

                myExpandedWeekItem = week;  //разворачиваемая неделя
                myExpandedDayOfWeek = dayOfWeek; //разворачиваемый день недели
                myExpandedDate = date; //разворачиваемая дата
                i.toBack(); //Шаг назад

                emit dateExpanded(date); //подать сигнал изменения даты
            }
        }
    }else
    {
        myExpandedDayOfWeek = 0; //Нет развернутого дня
        myExpandedDate = QDate(0,0,0); //Нет развернутой даты
    }

    layoutChanged(); //изменить layout

    if(myExpandedWeekItem != 0 && weekChanged)
        myExpandedWeekItem->ptrScrollArea->scrollTo(ptrStyle->quarterHeight * 4 * 7);
    //прокрутить область
}

/**
*	@param number - номер разворачиваемой недели.
*/
void QuickCalendarView::expandWeek(int number)
{
    QListIterator <WeekItem*> i(myWeeks); //Идем по неделям
    while(i.hasNext())
    {
        WeekItem *week = i.next();

        if(week->myDate.weekNumber() == number) //если номер недели равен указанному
        {
            expandWeek(week); //развернуть неделю
            i.toBack();
        }
    }
}

/**
*	@param week - разворачиваемая неделя.
*/
void QuickCalendarView::expandWeek(WeekItem *week)
{
    if(week != myExpandedWeekItem) //если текущая неделя не равна развернутой
    {
        myExpandedWeekItem = week; //установить развернутую неделю
    }else //иначе
    {
        if(myWeeks.count() > 1)
        {
            myExpandedWeekItem = 0; //Свернуть неделю
            myExpandedDayOfWeek = 0;
            myExpandedDate = QDate(0,0,0);
        }
    }

    layoutChanged(); //изменяем layout

    if(myExpandedWeekItem != 0)
        myExpandedWeekItem->ptrScrollArea->scrollTo(ptrStyle->quarterHeight * 4 * 7);
    //прокрутить область
}

/**
*	@return номер развернутой недели. Если никакие недели не развернуты, вернет 0.
*/
int QuickCalendarView::expandedWeekNumber() const
{
    if(myExpandedWeekItem != 0)
        return myExpandedWeekItem->myDate.weekNumber();
    else
        return 0;
}


/**
 * @brief QuickCalendarView::collapseAll
 */
void QuickCalendarView::collapseAll()
{
    if(myExpandedWeekItem != 0) //Если есть развернутая неделя
    {
        if(myWeeks.count() > 1) //если количество недель больше 1
        {
            myExpandedWeekItem = 0; //Сбросить все развернутые дни
            myExpandedDayOfWeek = 0;
            myExpandedDate = QDate(0,0,0);
            layoutChanged(); //изменить layout
        }
    }
}

/**
*	@param event - событие изменения размера.
*/
void QuickCalendarView::resizeEvent(QResizeEvent *event)
{
    layoutChanged(); //Изменить layout
}

void QuickCalendarView::layoutChanged()
{
    if(myWeeks.count() == 0) //Если кол-во отображаемых недель равно 0
        return; //выход

    int width = this->width(); //Запоминаем ширину и
    int height = this->height(); //высоту виджета


    setSceneRect(0,0,width,height); //Установим размер сцены

    // Вычисляем ширину рабочей области
    int workAreaWidth = width - ptrStyle->weekLeftMargin - ptrStyle->weekRightMargin;

    for(int i=0;i<21;i++)
        myDayWidths[i] = 0; //Обнуляем ширину дней

    int dayCount; //Количество дней в строке
    int firstDay = 0; //Первый день

    if(myDisplayMode == DisplayFullWeeks) //Если отображаем все недели
        dayCount = 7; //Кол-во дней 7
    else if(myDisplayMode == DisplayOnlyRange) //иначе
    {
        firstDay = myStartDate.dayOfWeek() - 1; //Установим первый отображаемый день
        dayCount = myStartDate.daysTo(myEndDate) + 1; //И их количество
    }

    if(dayCount > 1) //Если кол-во дней больше 1
    {
        if(myExpandedDayOfWeek != 0) //Если есть развернутый день недели
        {
            int expandedDayWidth = (workAreaWidth / 3) * 2; //Вычисляем его ширину
            workAreaWidth -= expandedDayWidth; //Вычитаем ее из размера раб. области
            int dayWidth = workAreaWidth / (dayCount - 1); //Вычислим ширину остальных дней
            int mod = workAreaWidth % (dayCount - 1); //Получаем остаток

            for(int i=firstDay;i<firstDay+dayCount;i++) //От первого дня до их количества
            {
                if(i == firstDay + myExpandedDayOfWeek - 1) //если этот день развернут
                {
                    myDayWidths[i] = expandedDayWidth + mod; //его ширина равна вычисленной + остаток
                }else
                {
                    myDayWidths[i] = dayWidth; //ширина свернутого дня
                }
            }
        }else
        {
            int dayWidth = workAreaWidth / dayCount; //Вычичисляем ширину дня
            int mod = workAreaWidth % dayCount; //Вычисляем остаток

            for(int i=firstDay;i<firstDay+dayCount;i++)
            {
                myDayWidths[i] = dayWidth; //запоминаем ширину всех дней
            }
            myDayWidths[firstDay] += mod; //К первому дню добавляем остаток
        }
    }else //Если кол-во дней не больше 1
    {
        myDayWidths[firstDay] = workAreaWidth; //Ширина первого дня равна всей рабочей области
    }

    //    for(int i=0;i<21;i++)
    //    {
    //        qDebug(qPrintable("W: [" + QString::number(i) + "] = " + QString::number(myDayWidths[i])));
    //    }

    int weekTop = 0;
    int weekHeight = 0;
    int expandedWeekHeight = 0;

    if(myWeekCount > 1) //если кол-во недель больше 1
    {
        int headerLeft = 0;
        int headerCount = 0;
        int headerHeight = 40 + (height - 40)%myWeeks.count();

        ptrHeader->setPos(ptrStyle->weekLeftMargin, 0); //Устанавливаем позицию панели выбора месяца и года
        ptrHeader->setSize(width, headerHeight); //Ее высоту
        ptrHeader->setVisible(true); //Делаем ее видимой

        QListIterator <QGraphicsItem *> i(ptrHeader->childItems());
        while(i.hasNext()) //идем по заголовкам дней недели
        {
            WeekDayHeaderItem *item = (WeekDayHeaderItem *)i.next();
            item->setPos(headerLeft, 0); //задаем их поцзицию
            item->setSize(myDayWidths[headerCount], headerHeight); //и размер
            item->layoutChanged();

            headerLeft += myDayWidths[headerCount]; //вычислеям положение след. заголовка

            headerCount++; //увеличиваем кол-во заголовков
        }

        weekTop = headerHeight; //Запоминаем высоту заголовков
    }else
    {
        ptrHeader->setVisible(false); //Спрячем заголовки дней недели
    }

    if(myExpandedWeekItem != 0) //Если есть развернутая неделя
    {
        expandedWeekHeight = (height - weekTop) - ((myWeekCount - 1) *
                                                   ptrStyle->collapsedWeekHeight()); //Вычислим ее высоту
        weekHeight = ptrStyle->collapsedWeekHeight(); //И высоту остальных недель
    }else
    {
        weekHeight = (height - weekTop)/myWeeks.count(); //Вычислим высоту всех недель
    }

    for(int i=0;i<myWeeks.count();i++) //идем по неделям
    {
        WeekItem *week = myWeeks.at(i);

        week->setPos(0, weekTop); //Задаем позицию недели
        if(week == myExpandedWeekItem) //Если ее нужно развернуть
        {
            week->setSize(width, expandedWeekHeight); //зададим особый размер
            weekTop += expandedWeekHeight;
        }else
        {
            week->setSize(width, weekHeight); //иначе обычный размер
            weekTop += weekHeight;
        }

        week->layoutChanged(); //обновим layout
    }

    //update();
}

/**
*	@param appointment - указатель на встречу, для которой выводится форма.
*/
void QuickCalendarView::showAppointmentForm(Appointment *appointment)
{
    bool someSelected = false;

    for(int i=0;i<ptrCalendars->count();i++)
    {
        if(ptrCalendars->at(i)->isSelected())
            someSelected = true;
    }

    if(!someSelected)
    {
        QMessageBox::warning(0, QObject::tr("Calendar error"), QObject::tr("Select at least one calendar first!"));
        return;
    }

    if(ptrCalendars->count() > 0)
    {
        AppointmentDetailsForm *form = new AppointmentDetailsForm(appointment,
                                                                  ptrCalendars);

        connect(form, SIGNAL(onClose(Appointment*)), this, SLOT(onFormClosed(Appointment*)));

        if(appointment->key() == 0)
            form->setCloseHidden(true);

        form->setGeometry(300,300,400,250);
        form->show();
    }
}

/**
 * @brief QuickCalendarView::dataChanged
 */
void QuickCalendarView::dataChanged()
{
    QListIterator <WeekItem *> i(myWeeks); //Идем по неделям
    while(i.hasNext())
    {
        WeekItem *week = i.next();
        week->dataChanged(); //вызываем у них метод dataChanged
    }
}
#include "publics.h"
/**
*	@param appointment - указатель на встречу, для которой выводилась форма.
*/
void QuickCalendarView::onFormClosed(Appointment *appointment)
{
    if(appointment != 0)
    {
        qDebug() << "AppointmentID " << appointment->key();
        QSqlDatabase db = Publics::getDatabase();
        if (db.isOpen()) {
            QString customerID = appointment->customerID();
            QString appointmentTypeID = QString::number(appointment->calendar()->key());
            QString del = "false";
            if (appointment->isComplete)
                del = "true";
            QSqlQuery saveQu =  db.exec("UPDATE appointments SET"
                                        " AppointmentType = '" + appointmentTypeID + "', "
                                        " CustomerID = '" + customerID + "', "
                                        " StartDate = '" + appointment->startDateTime().toString("yyyy-MM-dd") + "', "
                                        " StartTime = '" + appointment->startDateTime().toString("hh:mm:ss")+ "', "
                                        " EndDate = '" + appointment->endDateTime().toString("yyyy-MM-dd")+ "', "
                                        " EndTime = '" + appointment->endDateTime().toString("hh:mm:ss")+ "', "
                                        " Location = '" + appointment->place()+ "', "
                                        " Subject = '" + appointment->subject() + "', "
                                        " IsComplete = '" + del + "', "
                                        " Description = '" + appointment->description()+ "' "
                                        " WHERE AppointmentID = '" + QString::number(appointment->key()) + "'");
            if (saveQu.lastError().isValid()) {
                Publics::showError(saveQu.lastError().text());
            }
        }
        dataChanged();
        layoutChanged();
    }
}

/**
*	@param dayOfWeek - день недели, который необходимо развернуть.
*/
void QuickCalendarView::expandDayOfWeek(int dayOfWeek)
{
    if(myExpandedWeekItem != 0) //если есть развернутые недели
    {
        if(dayOfWeek != myExpandedDayOfWeek)  //И заданный день не равен развернутому
            myExpandedDayOfWeek = dayOfWeek; //зададим новый разворачиваемый день
        else
            myExpandedDayOfWeek = 0; //иначе свернем день

        layoutChanged(); //изменим выравнивание
    }
}
