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

#include <QtGui>
#include "clockbar.h"

/**
* @param parent -  указатель на родителя.
* @param scene - указатель на сцену.
*/
ClockBar::ClockBar(QGraphicsItem *parent, QGraphicsScene *scene) : 
	CalendarItem(parent, scene) //Вызов конструктора родителя
{
	prepareGeometryChange(); //Подготавливаем элемент для смены геометрии

	QFont font("Arial", 18, QFont::Normal); //Устанавливаем нужный шрифт
	QFontMetrics fm(font); //Задаем метрику шрифта
	myBoundingRect.adjust(0,0,10 + fm.width("MM"), 24*10*4);
	//Добавляем 0,0,10 + fm.width("MM") и 24*10*4 к имеющимся координатам прямоугольника, соответственно.
}

void ClockBar::paint(QPainter *painter,
		     const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	int width = (int)myBoundingRect.width(); //запоминаем ширину
	int height = (int)myBoundingRect.height(); //запоминаем высоту

	painter->setBrush(QBrush(QColor(200,200,200))); //Задаем кисть (цвет)
	painter->drawRect(0.5,0.5,width-0.5,height-0.5); //Рисуем прямоугольник

	QFont font("Arial", 18, QFont::Normal); //Задаем нужный шрифт
	QFontMetrics fm(font); //Задаем метрику шрифта
	QRectF hourRect(-5, 0, fm.width("MM"), fm.height()); // = fm.tightBoundingRect("MM"); //

	painter->setFont(font); //Уставаливаем шрифт
	painter->setPen(QPen(QColor(80,80,80))); //Устанавливаем цвет пера

	int y = 0;
	for(int i=0;i<24;i++) //От 0 часов до 24 часов
	{
		painter->drawLine(0,y,width,y); //Рисуем разделительную линию
		painter->drawText(hourRect, Qt::AlignRight, QString::number(i)); //Пишем номер часа
		hourRect.adjust(0, 4*10, 0, 4*10); //Добавляем к координатам прямоугольника 40
		y += 4*10; //Увеличиваем y на 40
	}

	font.setPixelSize(10); //Задаем размер пикселя
	painter->setFont(font); //Устанавливаем шрифт
	fm = painter->fontMetrics(); //Запоминаем метрику шрифта
	y = 0; //Сбрасываем y
	int x = hourRect.left() + hourRect.width(); //Вычисляем x как координату правого верхнего угла
	for(int i=0;i<24;i++) //24 раза
	{
		painter->drawText(x, y + fm.ascent(), "00"); //Дописываем 00 минут к цифре каждого часа
		y += 4*10; //Увеличиваем y
	}
}
