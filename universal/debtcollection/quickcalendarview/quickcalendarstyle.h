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

#ifndef QUICKCALENDARSTYLE_H
#define QUICKCALENDARSTYLE_H

#include <QFont>
#include <QList>
#include <QDate>
#include <QLinearGradient>
#include <QPen>

/**
* @class QuickCalendarStyle
* @brief Класс для хранения информации о внешнем виде календаря
*/
class QuickCalendarStyle
{

public:
	QuickCalendarStyle(); ///<Конструктор

	QFont weekNumberFont; ///<Шрифт цифр номера недели
	QFont dayNumberFont; ///<Шрифт цифр номера дня недели
	QFont dayNameFont; ///<Шрифт названия дня

	QFont appointmentSubjectFont; ///<Шрифт для отображения информации о встрече
	QFont clockBarFont; ///<Шрифт для списка часов от 0-00 до 23-00

	int weekLeftMargin; ///<Ширина столбика с номером недели
	int weekRightMargin; ///<Отступ справа от границы окна до столбика ВС
	int quarterHeight; ///<Высота получасовой ячейки

	int expandedWeekHeaderHeight; ///<Высота строки с номером недели и днями при развернутом дне

	QPen pastDayPen; ///<Перо, которым рисуются прошедшие числа
	QPen todayPen; ///<Перо, которым рисуется сегодняшнее число
	QPen comingDayPen; ///<Перо, которым рисуются будущие числа

	QLinearGradient pastDayGradient; ///<Градиент прошедшего дня
	QLinearGradient todayGradient; ///<Градиент сегодняшнего дня
	QLinearGradient comingDayGradient; ///<Градиент будущего дня

	QLinearGradient pastWeekendGradient; ///<Градиент прошедших выходных
	QLinearGradient weekendGradient; ///<Градиент текущих выходных
	QLinearGradient comingWeekendGradient; ///<Градиент будущих дня

	QFont expandedDayNumberFont; ///< Шрифт числа при развернутом дне недели
	QFont collapsedDayNumberFont; ///< Шрифт числа при свернутом дне недели

	int collapsedWeekHeight() const; ///<Метод, возвращающий высоту свернутой недели
};


#endif
