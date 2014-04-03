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

#include "calendartablemodel.h"

/**
* @param parent - указатель на предка.
*/
CalendarTableModel::CalendarTableModel(QObject *parent) :
	QAbstractTableModel(parent)
{
}

/**
* @param calendars - указатель на список календарей.
*/
void CalendarTableModel::setCalendars(QList <Calendar *> *calendars)
{
	ptrCalendars = calendars; //Запоминаем список календарей
	//reset(new QTextStream());  //Возвращает стандартный вид модели
}

/**
* @param parent - не используется.
* @return количество строк.
*/
int CalendarTableModel::rowCount(const QModelIndex &parent) const
{
	return ptrCalendars->count();
}

/**
* @param parent - не используется.
* @return всегда возвращает 2.
*/
int CalendarTableModel::columnCount(const QModelIndex &parent) const
{
	return 2;
}

/**
* @param index - индекс.
* @param role - роль. Может принимать значения Qt::TextAlignmentRole, Qt::BackgroundColorRole,
Qt::DisplayRole, Qt::CheckStateRole,Qt::EditRole,Qt::UserRole.
* @return если role == Qt::TextAlignmentRole, вернет информацию о выравнивании,
* @return если role == Qt::BackgroundColorRole, вернет цвет календаря с номером index,
* @return если role == Qt::DisplayRole, вернет имя календаря с номером index,
* @return если role == Qt::CheckStateRole, вернет статус выделения календаря с номером index.
* @return В остальных случаях или, если индекс не принадлежит модели, вернет QVariant().
*/
QVariant CalendarTableModel::data(const QModelIndex &index, int role) const
{
	if(!index.isValid()) //Если индекс не принадлежит модели
		return QVariant();  //вернуть пустой результат.

	if(role == Qt::TextAlignmentRole) //Если спрашиваем выравнивание
	{
		return int(Qt::AlignLeft | Qt::AlignVCenter); //Вернуть информацию о выравнивании
	}else if(role == Qt::BackgroundColorRole && index.column() == 0) //Если спрашиваем цвет
	{
		QColor color; //Запоминаем цвет
		if(index.row() < ptrCalendars->count()) //Если номер строки меньше количества календарей
			color = ptrCalendars->at(index.row())->color(); //запомнить цвет нужного календаря

		return color; //вернуть его
	}else if(role == Qt::DisplayRole) //Если спрашиваем имя календаря
	{
		if(index.row() < ptrCalendars->count()) //Если индекс меньше количества календарей
		{
			if(index.column() == 1) //и если номер столбца равен 1
				return ptrCalendars->at(index.row())->name(); //вернем имя календаря
		}
	}else if(role == Qt::EditRole && index.column() == 0)
	{
	}else if(role == Qt::UserRole)
	{
	}else if(role == Qt::CheckStateRole && index.column() == 0) //Если спрашивается статус выделения
	{
		return QVariant(ptrCalendars->at(index.row())->isSelected()); //вернем статус выделения строки
	}

	return QVariant();
}

/**
* @param section - не используется.
* @param orientation - не используется.
* @param role - не используется.
* @return всегда возвращает QVariant().
*/
QVariant CalendarTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

/**
* @param index - индекс.
* @param value - устанавливаемое значение. Не используется.
* @param role - роль. Описана только работа со значением Qt::CheckStateRole.
* @return true - в случае успешного изменения, false - в случае ошибки.
*/
bool CalendarTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	//если индекс верен и изменяем выделение
	if(index.isValid() && index.column() == 0 && role == Qt::CheckStateRole)
	{
		Calendar *calendar = ptrCalendars->at(index.row()); //получим нужный календарь
		if(calendar->isSelected()) //если он выбран
			calendar->setSelected(false); //снимем выделение
		else //иначе
			calendar->setSelected(true); //установим его

		//ptrCalendars->replace(index.row(), calendar);
		emit dataChanged(index, index); //высылаем сигнал изменения данных
		return true;
	}
	return false;
}

/**
* @param index - индекс ячейки.
* @return если номер столбца равен 0, вернет Qt::ItemIsUserCheckable.
*/
Qt::ItemFlags CalendarTableModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractItemModel::flags(index);
	if(index.column() == 0) //если номер столбца равен 0
	{
		flags |= Qt::ItemIsUserCheckable;  //Возможность выбора календаря пользователем
	}
	return flags;
}
