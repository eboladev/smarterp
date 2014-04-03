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

#ifndef QUICKCALENDARWINDOW_H
#define QUICKCALENDARWINDOW_H

#include <QColor>
#include <QIcon>
#include <QList>
#include <QMainWindow>
#include <QTableView>
#include "ui_quickcalendarwindow.h"
#include "quickcalendarview.h"
#include "selectorwidget.h"
#include "calendar.h"
#include "calendartablemodel.h"

/**
@class QuickCalendarWindow
@brief Класс, реализующий главное окно виджета
*/
/**
Пример использования:
@code 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QuickCalendarWindow *window = new QuickCalendarWindow();

    window->setGeometry(100,100,800,600);
    window->startUp();

    return app.exec();
}
@endcode
Создаем новый объект класса QuickCalendarWindow.
Устанавливаем его положение на экране или на родительском виджете, а также его размеры с помощью метода setGeometry(). 
Если добавить window как дочерний виджет, то положение будет задано в клиентской области родителя. 
Метод startUp() инициализирует окно календаря:
создает основные компоненты окна, связывает основные сигналы и слоты.
*/ 
class QuickCalendarWindow: public QMainWindow, public Ui::QuickCalendarWindow
{
	Q_OBJECT

public:
	///Конструктор
	QuickCalendarWindow();

	///Метод создает основные компоненты окна, связывает основные сигналы и слоты
	void startUp();

protected:
	void closeEvent(QCloseEvent *event); ///<Событие закрытия окна
	void createDockWidgets(); ///<Метод создает плавающий список календарей

private slots: 
	void onExit(); ///<Слот, вызываемый при закрытии виджета
	///Слот изменения списка выбранных календарей
	void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	void modeChanged(int mode); //<Слот изменения режима

private:
	///Метод добавляет 4 календаря и несколько событий
	void generateData();

	QList <QColor> myColors; ///<Вектор цветов
	QList <QIcon> myIcons;   ///<Вектор иконок

	QuickCalendarView *ptrCalendarView; ///<Виджет календарь (таблица дней месяца)
	SelectorWidget *ptrSelectorWidget; ///<Виджет выбора месяца
	QTableView *ptrTableView;
	CalendarTableModel *ptrCalendarModel; ///<Модель календарей

	QList <Calendar *> myCalendars; ///<Список календарей
};

#endif
