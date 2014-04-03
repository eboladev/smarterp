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
#include "quickcalendarstyle.h"

QuickCalendarStyle::QuickCalendarStyle() :
	weekNumberFont("arial", 30),  //Задаем значения по умолчанию
	dayNumberFont("arial", 24),
	dayNameFont("arial", 16),
	appointmentSubjectFont("arial", 16),
	clockBarFont("arial", 16),
	expandedDayNumberFont("Arial", 24),
	collapsedDayNumberFont("Arial", 18)
{

	weekLeftMargin = 50;
	weekRightMargin = 16;
	quarterHeight = 10;

	expandedWeekHeaderHeight = 40;

	pastDayGradient.setColorAt(0, QColor(199,199,199));
	pastDayGradient.setColorAt(1, QColor(191,191,191));

	todayGradient.setColorAt(0, QColor(229,182,114));
	todayGradient.setColorAt(1, QColor(229,153,45));

	comingDayGradient.setColorAt(0, QColor(255,255,255));
	comingDayGradient.setColorAt(1, QColor(215,215,215));

	pastWeekendGradient.setColorAt(0, QColor(169,169,169));
	pastWeekendGradient.setColorAt(1, QColor(161,161,161));

	weekendGradient.setColorAt(0, QColor(199,152,84));
	weekendGradient.setColorAt(1, QColor(199,123,15));

	comingWeekendGradient.setColorAt(0, QColor(225,225,225));
	comingWeekendGradient.setColorAt(1, QColor(185,185,185));

	pastDayPen.setColor(QColor(127,127,127));
	todayPen.setColor(QColor(0,0,0));
	comingDayPen.setColor(QColor(63,63,63));

}

/**
* @return всегда 30.
*/
int QuickCalendarStyle::collapsedWeekHeight() const
{
	return 30;
}
