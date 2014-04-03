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
#include "weekitem.h"
#include "dayitem.h"
#include "quickcalendarstyle.h"
#include "quickcalendarview.h"
#include <QStyle>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

WeekItem::WeekItem(QuickCalendarView *calendarView,
                   const QDate &start,
                   const QDate &end,
                   QGraphicsItem *parent,
                   QGraphicsScene *scene) :
    CalendarItem(parent, scene),
    ptrCalendarView(calendarView),
    myRangeStart(start),
    myRangeEnd(end)
{
    acceptHoverEvents();

    myFont = ptrCalendarView->style()->collapsedDayNumberFont;

    dayHeaderContainer = new CalendarItem(this);

    ptrScrollPane = new CalendarItem();
    clockBar = new ClockBar(ptrScrollPane);
    dayContentContainer = new CalendarItem(ptrScrollPane);

    ptrScrollArea = new ScrollAreaItem(this);
    ptrScrollArea->setItem(ptrScrollPane);

    if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayFullWeeks)
    {
        myDate = myRangeStart.addDays(-(myRangeStart.dayOfWeek() - 1));

        if(myDate.daysTo(myRangeEnd) > 6)
            myRangeEnd = myDate.addDays(6);

        for(int i=1;i<=7;i++)
        {
            DayItem *day = new DayItem(ptrCalendarView, myDate.addDays(i-1), dayHeaderContainer);
            day->ptrContentItem->setParentItem(dayContentContainer);

            if(myDate.addDays(i-1) < myRangeStart || myDate.addDays(i-1) > myRangeEnd)
            {
                day->setOutOfRange(true);
            }

            myDays.append(day);
        }
    }else if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayOnlyRange)
    {
        myDate = myRangeStart;

        for(int i=1;i<=myRangeStart.daysTo(myRangeEnd) + 1;i++)
        {
            DayItem *day = new DayItem(ptrCalendarView, myDate.addDays(i-1), dayHeaderContainer);
            day->ptrContentItem->setParentItem(dayContentContainer);

            myDays.append(day);
        }
    }
}

void WeekItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    painter->setClipRect(myBoundingRect);


    int gradientHeight = height;

    if(ptrCalendarView->expandedWeekItem() == this)
        gradientHeight = ptrCalendarView->style()->expandedWeekHeaderHeight;

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, gradientHeight));

    bool isCurrentWeek = QDate::currentDate().weekNumber() == myDate.weekNumber() &&
       QDate::currentDate().year() == myDate.year();

    if(isCurrentWeek)
    {
        linearGrad.setColorAt(0, QColor(239,210,168));
        linearGrad.setColorAt(1, QColor(229,173,94));
    }else
    {
        linearGrad.setColorAt(0, QColor(255,255,255));
        linearGrad.setColorAt(1, QColor(191,191,191));
    }

    painter->setBrush(linearGrad);
    painter->drawRect(0,0,width,height);

    if(option->state & QStyle::State_MouseOver)
    {
        if(isCurrentWeek)
            painter->setBrush(QColor(255, 255, 255, 97));
        else
            painter->setBrush(QColor(56, 128, 189, 97));

        painter->drawRect(0,0,width,height);
    }

    // Week header
    QFontMetrics fm(myFont);
    painter->setFont(myFont);
    painter->drawText(10, fm.ascent() + 3, QString::number(myDate.weekNumber()));
}

bool WeekItem::hasDate(const QDate &date)
{
    if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayFullWeeks)
    {
        if(date >= myDate && date <= myDate.addDays(6))
            return true;
        else
            return false;
    }else if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayOnlyRange)
    {
        if(date >= myRangeEnd && date <= myRangeEnd)
            return true;
        else
            return false;
    }

    return false;
}

int WeekItem::dayOfWeek(const QDate &date)
{
    if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayFullWeeks)
    {
        if(date >= myDate && date <= myDate.addDays(6))
            return date.dayOfWeek();
        else
            return -1;
    }else if(ptrCalendarView->displayMode() == QuickCalendarView::DisplayOnlyRange)
    {
        if(date >= myRangeStart && date <= myRangeEnd)
            return myRangeStart.daysTo(date) + 1;
        else
            return -1;
    }

    return -1;
}

void WeekItem::dataChanged()
{
    QListIterator <DayItem *> i(myDays);
    while(i.hasNext())
    {
        DayItem *day = i.next();
        day->dataChanged();
    }
}

void WeekItem::layoutChanged()
{
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    QuickCalendarStyle *style = ptrCalendarView->style();

    clockBar->setSize(style->weekLeftMargin, style->quarterHeight * 4 * 24);

    int headerHeight = style->expandedWeekHeaderHeight;
    int workWidth = width - style->weekLeftMargin - style->weekRightMargin;

    dayHeaderContainer->setPos(style->weekLeftMargin, 0);
    if(ptrCalendarView->expandedWeekItem() == this)
    {
        dayHeaderContainer->setSize(workWidth, style->expandedWeekHeaderHeight);

        dayContentContainer->setPos(style->weekLeftMargin, 0);
        dayContentContainer->setSize(workWidth, style->quarterHeight * 4 * 24);

        ptrScrollPane->setSize(workWidth, style->quarterHeight * 4 * 24);
        ptrScrollArea->setPos(0, style->expandedWeekHeaderHeight);
        ptrScrollArea->setSize(width, height - style->expandedWeekHeaderHeight);
        ptrScrollArea->setVisible(true);
    }else
    {
        dayHeaderContainer->setVisible(true);
        dayHeaderContainer->setSize(workWidth, height);
        headerHeight = height;
        ptrScrollArea->setVisible(false);
    }

    int dayLeft = 0;
    int dayOfWeek = myDate.dayOfWeek() - 1;
    QListIterator <DayItem *> i(myDays);
    while(i.hasNext())
    {
        DayItem *day = i.next();
        int dayWidth = ptrCalendarView->dayWidth(dayOfWeek);
        day->setPos(dayLeft,0);
        day->setSize(dayWidth, headerHeight);
        dayLeft += dayWidth;

        day->layoutChanged();

        dayOfWeek++;
    }
}

void WeekItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
 }

void WeekItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void WeekItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //event->pos().x() > ptrMonthItem->myStyle.weekLeftMargin + clockWidth
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }

    ptrCalendarView->expandWeek(this);
}


