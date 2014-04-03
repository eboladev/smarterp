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

#ifndef SELECTORWIDGET_H
#define SELECTORWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QDate>
#include <QStackedLayout>
#include <QDateEdit>
#include <QCheckBox>

class SelectorWidget : public QWidget
{
	Q_OBJECT

public:
	SelectorWidget(QWidget *parent = 0);

	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	int maximumHeight() const;
	QSize maximumSize() const;
	//QSizePolicy sizePolicy() const;

	QDate date(){ return myDate;}
	void setDate(QDate date);

signals:
	void monthChanged(int year, int month);
	void rangeChanged(const QDate &start, const QDate &end);
	void modeChanged(int mode);

public slots:
	void showMonthBased();
	void showWeekBased();
	void showDayBased();
	void showRangeBased();

private slots:
	void onMonthChanged(int month);
	void onYearChanged(int year);
	void previous();
	void next();
	void valueChanged(int i);
	void dateChanged(const QDate &date);
	void weekStateChanged(int state);

private:
	int state;

	QDate myDate;

	QComboBox *monthCombo;
	QComboBox *yearCombo;

	QSpinBox *weekSpin;
	QSpinBox *daySpin;

	QDateEdit *start;
	QDateEdit *end;

	QCheckBox *multiWeek;

	QStackedLayout *stackedLayout;
};

#endif
