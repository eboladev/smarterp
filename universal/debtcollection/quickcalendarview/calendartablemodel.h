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

#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include <QList>
#include <QModelIndex>

#include "calendar.h"

/**
* @class CalendarTableModel
* @brief Табличная модель календарей
*/
class CalendarTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	CalendarTableModel(QObject *parent = 0); ///<Конструктор
	~CalendarTableModel() {} ///<Деструктор

	void setCalendars(QList<Calendar *> *calendars); ///<Метод установки адреса списка календарей

	///Метод чтения количества строк
	int rowCount(const QModelIndex & parent = QModelIndex()) const;
	///Метод чтения количества столбцов
	int columnCount(const QModelIndex & parent = QModelIndex()) const;
	///Вернет информацию о данных календаря с номером index в зависимости от role.
	QVariant data(const QModelIndex &index, int role) const;
	///Метод возвращает информацию о заголовках
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	///Если role == Qt::CheckStateRole, изменит статус выделения календаря с номером index на противоположный.
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	///Вернет возможность выбора пользователем календаря с номером index
	Qt::ItemFlags flags(const QModelIndex &index) const;

private:
	QList <Calendar *> *ptrCalendars; ///<Адрес списка календарей
};

#endif
