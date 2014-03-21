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
#include <QStyle>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>


#include "weekdayheaderitem.h"
#include "quickcalendarview.h"

WeekDayHeaderItem::WeekDayHeaderItem(QuickCalendarView *calendarView,
                                     int dayOfWeek,
                                     QGraphicsItem *parent,
                                     QGraphicsScene *scene) :
    CalendarItem(parent, scene),
    ptrCalendarView(calendarView),
    myDayOfWeek(dayOfWeek),
    myDayTitle(QDate::longDayName(dayOfWeek)),
    myAlign(Qt::AlignCenter)
{
}

void WeekDayHeaderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFontMetrics fm(myFont);
    painter->setFont(myFont);
    painter->setPen(myPen);
    painter->setBrush(myGradient);
    painter->drawRect(myBoundingRect);
    painter->drawText(myBoundingRect, myAlign, myDayTitle);
    setAcceptHoverEvents(true);

    if(option->state & QStyle::State_MouseOver &&
       ptrCalendarView->expandedWeekItem() != 0)
    {
        painter->setBrush(QColor(56, 128, 189, 97));
        painter->drawRect(0,0,myBoundingRect.width(),myBoundingRect.height());
    }
}

void WeekDayHeaderItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void WeekDayHeaderItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void WeekDayHeaderItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ptrCalendarView->expandDayOfWeek(myDayOfWeek);
}

void WeekDayHeaderItem::layoutChanged()
{
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    QuickCalendarStyle *style = ptrCalendarView->style();

    myFont = style->collapsedDayNumberFont;
    myDayTitle.clear();

    QFontMetrics fm(myFont);
    if(fm.width(QDate::longDayName(myDayOfWeek)) + 10 < width)
    {
        myDayTitle.append(QDate::longDayName(myDayOfWeek));
        myAlign = Qt::AlignCenter | Qt::AlignVCenter;
    }else
    {
        myDayTitle.append(QDate::shortDayName(myDayOfWeek));

        if(fm.width(myDayTitle) > width)
        {
            myAlign = Qt::AlignLeft | Qt::AlignVCenter;
        }else{
            myAlign = Qt::AlignCenter | Qt::AlignVCenter;
        }
    }

    if(myDayOfWeek < 6)
        myGradient = style->comingDayGradient;
    else
        myGradient = style->comingWeekendGradient;

    myGradient.setFinalStop(0,height);
    myPen = style->comingDayPen;
}
