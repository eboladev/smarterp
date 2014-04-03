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

#ifndef QUICKCALENDARVIEW_H
#define QUICKCALENDARVIEW_H

#include <QGraphicsView>
#include <QList>

#include "calendaritem.h"
#include "quickcalendarstyle.h"
#include "weekitem.h"
#include "calendar.h"
#include "appointment.h"

/**
* @class QuickCalendarView
* @brief Класс для отображения содержимого календаря
*/ 
class QuickCalendarView : public QGraphicsView
{
	Q_OBJECT

public:
	QuickCalendarView(QWidget *parent = 0); ///<Конструктор
	~QuickCalendarView() {} ///<Пустой деструктор

	/*!
   *  Перечисление способов отображения:
   *         -# Отображать полные недели
   *         -# Отображать только диапазон
   */
	enum DisplayMode{
		DisplayFullWeeks = 0,
		DisplayOnlyRange = 1
	};

	/*!
    *	Метод вернет способ отображения.
    *	@return способ отображения.
    */
	int displayMode() const { return myDisplayMode; }

	/*!
    *	Метод вернет номер развернутого дня недели.
    *	@return номер развернутого дня недели. Если все дни свернуты, вернет 0.
    */
	int expandedDayOfWeek() const { return myExpandedDayOfWeek; }

	int expandedWeekNumber() const; ///<Вернет информацию о развернутой неделе

	/*!
    *	Метод вернет развернутую неделю.
    *	@return развернутую неделю.
    */
	WeekItem* expandedWeekItem() const { return myExpandedWeekItem; }

	/*!
    *	Метод вернет количество отображаемых недель.
    *	@return количество отображаемых недель.
    */
	int weekCount() const { return myWeekCount; }

	/*!
    *	Метод вернет ширину столбика в календаре.
	*	@param dayOfWeek - номер столбика.
    *	@return если dayOfWeek от нуля до 21 вернет ширину нужного столбкика. Иначе вернет 0.
    */
	int dayWidth(int dayOfWeek) const {
		if(dayOfWeek >= 0 && dayOfWeek < 21) return myDayWidths[dayOfWeek]; else return 0;
	}

	/*!
    *	Метод вернет информацию о внешнем виде календаря.
    *	@return информацию о внешнем виде календаря.
    */
	QuickCalendarStyle* style() const { return ptrStyle; }

	/*!
    *	Метод вернет список календарей.
    *	@return список календарей.
    */
	QList <Calendar*>* calendars() { return ptrCalendars; }

signals:
	void dateExpanded(const QDate &date); ///< Сигнал разворачивания даты

public slots:
	void expandDate(const QDate &date); ///<Метод разворачивает указанную дату
	void expandDayOfWeek(int dayOfWeek); ///<Метод разворачивает указанный день недели
	void expandWeek(int weekNumber); ///<Метод разворачивает указанную неделю
	void expandWeek(WeekItem *week); ///<Метод разворачивает указанную неделю
	void collapseAll(); ///<Метод сворачивает все элементы календаря

	void setRange(const QDate &start, const QDate &end); ///<Устанавливает отображаемый диапазон времени
	void setMonth(int year, int month); ///<Метод установит текущий отображаемый месяц и год

	void setDisplayMode(DisplayMode mode); ///<Метод устанавливает способ отображения
	void setCalendars(QList <Calendar *> *calendars); ///<Метод устанавливает список календарей

	void showAppointmentForm(Appointment *appointment); ///<Метод отображает форму настройки встречи

	void dataChanged(); //Метод вызывает метод dataChanged() у всех отображаемых недель
	void layoutChanged(); ///<Метод задает положение всех элементов календаря

protected:
	void resizeEvent(QResizeEvent *event); ///< Обработчик события изменения размера

private slots:
	void onFormClosed(Appointment *appointment); ///<Слот, вызываемый при закрытии формы настройки встречи

private:
	int myWeekMode;
	int myDisplayMode; ///<Способ отображения

	QDate myStartDate; ///<Начало недели, с которой начинается отображение
	QDate myEndDate; ///<Конец недели, которой заканчивается отображение

	QDate myRangeStart; ///<Дата, с которой начинается отображение
	QDate myRangeEnd; ///<Дата, которой заканчивается отображение

	QDate myExpandedDate; ///<Развернутая дата

	int myWeekCount; ///<Количество отображаемых недель

	CalendarItem *ptrHeader; ///<Панель выбора месяца и года
	CalendarItem *ptrContentPane; ///<Панель для отображения содержимого календаря

	QList <WeekItem *> myWeeks; ///<Список недель

	int myExpandedDayOfWeek; ///<Номер развернутого дня недели
	WeekItem *myExpandedWeekItem; ///<Развернутая неделя

	QuickCalendarStyle *ptrStyle; ///<Информация о внешнем виде календаря

	int myDayWidths[21]; ///<Вектор, хранящий ширину всех верт. столбцов календаря

	QList <Calendar *> *ptrCalendars; ///<Список календарей
};

#endif // QUICKCALENDARVIEW_H
