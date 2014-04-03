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

#include "quickcalendarwindow.h"
#include "quickcalendarview.h"

QuickCalendarWindow::QuickCalendarWindow()
{
	setupUi(this); //Устанавливаем разработанную в QT Desiner форму

	myColors << QColor(56, 128, 189)
		 << QColor(249, 162, 57)
		 << QColor(0, 139, 70)
		 << QColor(237, 19, 93)
		 << QColor(165, 93, 38)
		 << QColor(239, 71, 63)
		 << QColor(132, 199, 112)
		 << QColor(0, 90, 157); //Формируем вектор цветов

	QListIterator <QColor> i(myColors); //Список итераторов
	while(i.hasNext()) //Идем по списку
	{
		QColor color = i.next(); //Получаем цвет
		QPixmap pixmap(24, 24); //Создаем изображение размером 24 на 24
		pixmap.fill(color); //Заливаем его цветом
		QIcon icon; //Создаем иконку
		icon.addPixmap(pixmap); //Добавляем к ней изображение
		myIcons.append(icon); //Добавляем иконку к вектору
	}

	ptrCalendarModel = new CalendarTableModel(); //Создаем модель календарей
	ptrCalendarModel->setCalendars(&myCalendars); //Добавляем к ней список календарей

	generateData(); //Заполняем список календарей
}

void QuickCalendarWindow::generateData()
{
	// Holiday calendar

	Calendar *cal = new Calendar(0); //Создаем 0ой календарь
	cal->setName("Holiday Calendar"); //Устанавливаем его имя
	cal->setColor(myColors.at(0)); //Устанавливаем его цвет
	cal->setSelected(false); //Устанавливаем статус выделения
	myCalendars.append(cal); //Добавляем его к списку календарей

	Appointment *app = new Appointment(); //Создаем новую встречу
	app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(19,0,0)),
			  QDateTime(QDate(2008,12,23),QTime(23,0,0))); //Период события

	app->setSubject("Holiday party!"); //Устанавливаем субъект встречи
	app->setPlace("Secret place"); //Устанавливаем место встречи
	app->setDescription("Secret holiday party at secret place. Everybody is welcome!"); //Описание встречи
	cal->insertAppointment(app); //Добавляем встречу к календарю

	app = new Appointment();//Создаем новую встречу
	app->setDateTimes(QDateTime(QDate(2008,12,24),QTime(12,0,0)),
			  QDateTime(QDate(2008,12,24),QTime(23,59,0)));//Период события

	app->setSubject("Christmas party!"); //Устанавливаем субъект встречи
	app->setPlace("Everywhere"); //Устанавливаем место встречи
	app->setDescription("Everybody is welcome!"); //Описание встречи
	cal->insertAppointment(app); //Добавляем встречу к календарю

	// Work Calendar

	cal = new Calendar(1);//Создаем 1ый календарь
	cal->setName("Work Calendar");//Устанавливаем его имя
	cal->setColor(myColors.at(1));//Устанавливаем его цвет
	cal->setSelected(false);//Устанавливаем статус выделения
	myCalendars.append(cal);//Добавляем его к списку календарей

	app = new Appointment(); //Создаем новую встречу
	app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(9,0,0)),
			  QDateTime(QDate(2008,12,22),QTime(11,00,0)));//Период события
	app->setSubject("Meeting"); //Устанавливаем субъект встречи
	app->setPlace("Somewhere"); //Устанавливаем место встречи
	app->setDescription("Remember this meeting!"); //Описание встречи
	cal->insertAppointment(app); //Добавляем встречу к календарю

	app = new Appointment(); //Создаем новую встречу
	app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(11,00,0)),
			  QDateTime(QDate(2008,12,22),QTime(12,30,0))); //Период события
	app->setSubject("Lunch with Boss"); //Устанавливаем субъект встречи
	app->setPlace("Hilton"); //Устанавливаем место встречи
	app->setDescription("Good food."); //Описание встречи
	cal->insertAppointment(app); //Добавляем встречу к календарю

	app = new Appointment(); //Создаем новую встречу
	app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(10,00,0)),
			  QDateTime(QDate(2008,12,23),QTime(11,00,0))); //Период события
	app->setSubject("Call to collegue"); //Устанвливем субъект встречи
	cal->insertAppointment(app); //Добавляем встречу к календарю

	// QuickCalendar

	cal = new Calendar(2); //Создаем 2ой календарь
	cal->setName("QuickCalendar"); //Устанавливаем его имя
	cal->setColor(myColors.at(2)); //Устанавливаем его цвет
	cal->setSelected(false); //Устанавливаем статус выделения
	myCalendars.append(cal); //Добавляем его к списку календарей

	//Аналогичным образом добавляем примеры встреч//

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(8,0,0)),
			  QDateTime(QDate(2008,12,22),QTime(23,59,0)));
	app->setSubject("Rewrite QuickCalendar");
	app->setPlace("Home");
	app->setDescription("Rewrite QuickCalendar to better meet contest requirements.");
	cal->insertAppointment(app);

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(8,0,0)),
			  QDateTime(QDate(2008,12,23),QTime(23,59,0)));
	app->setSubject("Finish QuickCalendar");
	app->setPlace("Home");
	app->setDescription("Make QuickCalendar as ready as possible!");
	cal->insertAppointment(app);

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,27),QTime(10,0,0)),
			  QDateTime(QDate(2008,12,27),QTime(18,30,0)));
	app->setSubject("Design and implement new features");
	app->setPlace("Home");
	app->setDescription("Design and implement new features!");
	cal->insertAppointment(app);

	// Personal Calendar

	cal = new Calendar(3); //Создаем 3ий календарь аналогично
	cal->setName("Personal calendar");
	cal->setColor(myColors.at(3));
	cal->setSelected(false);
	myCalendars.append(cal);

	//Аналогичным образом добаляем встречи
	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(16,0,0)),
			  QDateTime(QDate(2008,12,23),QTime(19,0,0)));
	app->setSubject("Shopping");
	app->setPlace("Everywhere");
	app->setDescription("Buy some Christmas presents!");
	cal->insertAppointment(app);

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,26),QTime(10,0,0)),
			  QDateTime(QDate(2008,12,26),QTime(23,59,0)));
	app->setSubject("Family meeting");
	app->setPlace("Pamis");
	app->setDescription("Do not miss this!");
	cal->insertAppointment(app);

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,27),QTime(19,0,0)),
			  QDateTime(QDate(2008,12,27),QTime(23,59,0)));
	app->setSubject("Dining with friends");
	app->setPlace("Downtown");
	app->setDescription("");
	cal->insertAppointment(app);

	app = new Appointment();
	app->setDateTimes(QDateTime(QDate(2008,12,28),QTime(8,0,0)),
			  QDateTime(QDate(2008,12,28),QTime(23,59,0)));
	app->setSubject("Try to relax...");
	app->setPlace("Home");
	app->setDescription("Relax after \"hard\" week.");
	cal->insertAppointment(app);
}

void QuickCalendarWindow::startUp()
{
	QWidget *central = new QWidget(this); //Создаем центральный виджет
	QVBoxLayout *layout = new QVBoxLayout(central); //Создаем менеджер вертикального выравнивания
	layout->setMargin(0); //Задаем отступ

	ptrSelectorWidget = new SelectorWidget(this); //Создаем виджет выбора месяца и года, недели
	layout->addWidget(ptrSelectorWidget); //Добавляем его в layout

	ptrCalendarView = new QuickCalendarView(); //Создаем непосредственно календарь
	ptrCalendarView->setCalendars(&myCalendars); //Добавляем к нему список календарей (встречи)
	ptrCalendarView->setMonth(QDate::currentDate().year(), QDate::currentDate().month()); //Устанавлваем год и месяц
	layout->addWidget(ptrCalendarView); //Добавляем в layout

	central->setLayout(layout); //Устанавливаем layout на центральный виджет

	setCentralWidget(central); //Делаем central центральными виджетом окна

	createDockWidgets(); //Создаем виджеты в левой части окна (панель календарей)

	//Связываем сигналы и слоты
	connect(ptrSelectorWidget, //виджет выбора месяца
		SIGNAL(monthChanged(int, int)), //сигнал смены месяца или года
		ptrCalendarView, //Календарь
		SLOT(setMonth(int, int))); //Слот установки месяца и года

	connect(ptrSelectorWidget, //виджет выбора месяца
		SIGNAL(rangeChanged(const QDate &, const QDate &)), //сигнал изменения диапазона
		ptrCalendarView, //Календарь
		SLOT(setRange(const QDate &, const QDate &))); //слот установки диапазона

	connect(ptrSelectorWidget,//виджет выбора месяца
		SIGNAL(modeChanged(int)), //сигнал смены режима
		this, //главное окно
		SLOT(modeChanged(int))); //слот смены режима

	//Связываем сигналы объектов действий с соответствующими слотами
	connect(monthAction, SIGNAL(triggered()),
		ptrSelectorWidget, SLOT(showMonthBased()));
	connect(weekAction, SIGNAL(triggered()),
		ptrSelectorWidget, SLOT(showWeekBased()));
	//    connect(dayAction, SIGNAL(triggered()),
	//            ptrSelectorWidget, SLOT(showDayBased()));
	connect(rangeAction, SIGNAL(triggered()),
		ptrSelectorWidget, SLOT(showRangeBased()));

	show();
}

void QuickCalendarWindow::onExit()
{
	exit(0); //Выход
}

void QuickCalendarWindow::closeEvent(QCloseEvent *event)
{

}

void QuickCalendarWindow::createDockWidgets()
{
	ptrTableView = new QTableView(); //Создаем панель календарей
	ptrTableView->setModel(ptrCalendarModel); //Добавляем к ней модель календарей
	ptrTableView->setSelectionMode(QAbstractItemView::NoSelection); //Устанавливаем режим выделения
	ptrTableView->setGridStyle(Qt::NoPen); //Устанавливаем вид пера
	ptrTableView->setDragDropMode(QAbstractItemView::NoDragDrop); //Устанавливаем режим перетаскивания
	//Зачем-то 2ой раз устанавливаем режим выделения
	ptrTableView->setSelectionMode(QAbstractItemView::NoSelection);
	ptrTableView->horizontalHeader()->hide(); //Скрываем заголовки столбцов
	ptrTableView->verticalHeader()->hide(); //Скрываем заголовки строк
	ptrTableView->resizeColumnsToContents(); //Устанавливаем ширину ячеек по содержимому
	
	QVBoxLayout *layout = new QVBoxLayout(); //Создаем менеджер вертикального выравнивания
	layout->setMargin(0); //Устанавливаем отступ
	layout->addWidget(ptrTableView); //Добавляем в layout панель календарей

	QWidget *widget = new QWidget(); //Создаем виджет
	widget->setLayout(layout); //Добавляем к нему менеджер выравнивания
	widget->setGeometry(0,0,100,100); //Устанавливаем геометрию

	QDockWidget *dock = new QDockWidget(tr("Calendars"), this); //Создаем "плавающий" виджет
	//Устанавливаем области крепления к основному окну
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, dock); //Крепим виджет к окну
	dock->setWidget(widget); //Добавляем панель календарей

	//Связываем сигнал изменения списка выбранных календарей с соотв. слотом окна
	connect(ptrCalendarModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
}


void QuickCalendarWindow::dataChanged(const QModelIndex &topLeft,
				      const QModelIndex &bottomRight)
{
	ptrCalendarView->dataChanged(); //Изменяем данные
	ptrCalendarView->layoutChanged();  //Изменяем выравнивание

	//update();
}

/**
* @param mode - номер режима.
*/
void QuickCalendarWindow::modeChanged(int mode)
{
	if(mode == 0) //Если номер режима равен 0
	{
		ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayFullWeeks); //Отображаем полные недели
	}else
	{
		ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayOnlyRange); //Иначе только диапазон
	}
}
