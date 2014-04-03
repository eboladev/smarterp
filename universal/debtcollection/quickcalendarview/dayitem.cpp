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

#include "dayitem.h"
#include "weekitem.h"
#include "daycontentitem.h"
#include "appointmentitem.h"
#include "quickcalendarview.h"
#include "quickcalendarstyle.h"

DayItem::DayItem(QuickCalendarView *calendarView,
		 const QDate &date,
		 QGraphicsItem *parent,
		 QGraphicsScene *scene) :
	CalendarItem(parent, scene),
	ptrCalendarView(calendarView),
	myDate(date),
	myClockIcon("clockicon.png")
{
	ptrContentItem = new DayContentItem(this);
	amIOutOfRange = false;

	setAcceptHoverEvents(true);
}


void DayItem::paint(QPainter *painter,
		    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	int width = (int)myBoundingRect.width();
	int height = (int)myBoundingRect.height();

	painter->setClipRect(myBoundingRect);

	if(amIOutOfRange)
		painter->setBrush(QColor(127,127,127));
	else
		painter->setBrush(myGradient);

	painter->drawRect(0,0,width,height);

	if(option->state & QStyle::State_MouseOver)
	{
		if(myDate == QDate::currentDate())
			painter->setBrush(QColor(255, 255, 255, 97));
		else
			painter->setBrush(QColor(56, 128, 189, 97));

		painter->drawRect(0,0,width,height);
	}

	QFontMetrics fm(myFont);

	painter->setFont(myFont);

	if(amIOutOfRange)
		painter->setPen(QColor(63,63,63));
	else
		painter->setPen(myPen);

	painter->drawText(5, 5, width-5, height, myAlign, myCaption);

	if(myAppointments.count() > 0 && ptrCalendarView->weekCount() > 1)
	{
		int iconLeft = fm.width(QString::number(myDate.day()));
		painter->drawPixmap(iconLeft + 10, fm.height() - fm.ascent() + 1, myClockIcon);
	}
}

void DayItem::dataChanged()
{
	myAppointments.clear();

	QListIterator <Calendar *> i(*ptrCalendarView->calendars());
	while(i.hasNext())
	{
		Calendar *cal = i.next();
		if(cal->isSelected())
		{
			QListIterator <Appointment *> j(cal->getAppointments(myDate));
			while(j.hasNext())
			{
				Appointment *app = j.next();
				myAppointments.append(app);
			}
		}
	}

	qSort(myAppointments.begin(), myAppointments.end(), Appointment::before);
	ptrContentItem->dataChanged();

}

///Обработчи изменения слоя
void DayItem::layoutChanged()
{
	int left = (int)this->pos().x();
	int width = (int)myBoundingRect.width();
	int height = (int)myBoundingRect.height();

	QuickCalendarStyle *style = ptrCalendarView->style();

	ptrContentItem->setPos(left,0);
	ptrContentItem->setSize(width, style->quarterHeight * 4 * 24);

	if(myDate < QDate::currentDate())
	{
		if(myDate.dayOfWeek() < 6)
			myGradient = style->pastDayGradient;
		else
			myGradient = style->pastWeekendGradient;

		myGradient.setFinalStop(0,height);

		myPen = style->pastDayPen;
	}else if(myDate == QDate::currentDate())
	{
		if(myDate.dayOfWeek() < 6)
			myGradient = style->todayGradient;
		else
			myGradient = style->weekendGradient;

		myGradient.setFinalStop(0,height);

		myPen = style->todayPen;
	}else
	{
		if(myDate.dayOfWeek() < 6)
			myGradient = style->comingDayGradient;
		else
			myGradient = style->comingWeekendGradient;

		myGradient.setFinalStop(0,height);

		myPen = style->comingDayPen;
	}

	if(ptrCalendarView->expandedWeekItem() != 0)
	{
		if(ptrCalendarView->expandedWeekItem()->hasDate(myDate))
		{
			myFont = style->expandedDayNumberFont;
		}else
		{
			myFont = style->collapsedDayNumberFont;
		}
	}else
	{
		myFont = style->dayNumberFont;
	}

	if(ptrCalendarView->weekCount() == 1)
	{
		// QString longCaption =  myDate.longDayName(myDate.dayOfWeek())  + " " + QString::number(myDate.day()) + "/" + QString::number(myDate.month());
		QString longCaption = myDate.longDayName(myDate.dayOfWeek()) + " " + QString::number(myDate.day()) + " " + myDate.toString("MMMM");
		myFont = QFont("Calibri", 10, QFont::Light);
		QFontMetrics fm(myFont);
		myAlign = Qt::AlignVCenter;

		if(fm.width(longCaption) + 10 < width)
		{
			myCaption = longCaption;
			myAlign |= Qt::AlignCenter;
		}else
		{
			//  myCaption =
			//         myDate.shortDayName(myDate.dayOfWeek()).left(3) + " " + QString::number(myDate.day()) + "/" + QString::number(myDate.month()) + "\n" + QString::number(myDate.year()) ;

			myCaption = myDate.shortDayName(myDate.dayOfWeek()) + " " + QString::number(myDate.day());

			if(fm.width(myCaption) < width)
				myAlign |= Qt::AlignCenter;
			else
				myAlign |= Qt::AlignLeft;
		}

	}else
	{
		myCaption = QString::number(myDate.day());
		myAlign = Qt::AlignLeft;
	}


	ptrContentItem->layoutChanged();
	update();
}


void DayItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void DayItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

}

void DayItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	ptrCalendarView->expandDate(myDate);

}
