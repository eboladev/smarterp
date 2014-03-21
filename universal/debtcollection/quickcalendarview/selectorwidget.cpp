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

#include "selectorwidget.h"

SelectorWidget::SelectorWidget(QWidget *parent)    :
    QWidget(parent)
{
    state = 0;

    QWidget *monthBasedWidget = new QWidget;
    QWidget *weekBasedWidget = new QWidget;
    QWidget *dayBasedWidget = new QWidget;
    QWidget *rangeBasedWidget = new QWidget;

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(monthBasedWidget);
    stackedLayout->addWidget(weekBasedWidget);
    stackedLayout->addWidget(dayBasedWidget);
    stackedLayout->addWidget(rangeBasedWidget);

    // Month Based

    QHBoxLayout *monthLayout = new QHBoxLayout();

    QSpacerItem *leftSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    monthLayout->addItem(leftSpacer);

    QPushButton *prevMonth = new QPushButton(QIcon("leftarrow.png"), "");
    monthLayout->addWidget(prevMonth);

    monthCombo = new QComboBox;

    for (int month = 1; month <= 12; ++month)
        monthCombo->addItem(QDate::longMonthName(month));

    monthCombo->setMaxVisibleItems(12);
    monthLayout->addWidget(monthCombo);

    yearCombo = new QComboBox;

    for (int year = 2000; year < 2003; ++year)
        yearCombo->addItem(QString::number(year));

    setDate(QDate::currentDate());

    monthLayout->addWidget(yearCombo);
    monthLayout->setMargin(0);

    monthCombo->setBackgroundRole(QPalette::NoRole);
    monthCombo->setFont(QFont("arial", 18));    
    yearCombo->setBackgroundRole(QPalette::NoRole);
    yearCombo->setFont(QFont("arial", 18));

    QPushButton *nextMonth = new QPushButton(QIcon("rightarrow.png"), "");
    monthLayout->addWidget(nextMonth);

    QSpacerItem *rightSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    monthLayout->addItem(rightSpacer);

    monthBasedWidget->setLayout(monthLayout);

    // Week Based
    QHBoxLayout *weekLayout = new QHBoxLayout();

    QSpacerItem *weekLeftSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    weekLayout->addItem(weekLeftSpacer);
    weekLayout->setMargin(0);

    QPushButton *prevWeek = new QPushButton(QIcon("leftarrow.png"), "");
    weekLayout->addWidget(prevWeek);

    weekSpin = new QSpinBox();
    weekSpin->setValue(3);
    weekSpin->setMinimum(1);
    weekSpin->setMaximum(8);
    weekSpin->setSingleStep(1);
    weekSpin->setFrame(false);
    weekSpin->setBackgroundRole(QPalette::NoRole);
    weekSpin->setFont(QFont("arial", 18));

    weekLayout->addWidget(weekSpin);

    QPushButton *nextWeek = new QPushButton(QIcon("rightarrow.png"), "");
    weekLayout->addWidget(nextWeek);

    QSpacerItem *weekRightSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    weekLayout->addItem(weekRightSpacer);

    weekBasedWidget->setLayout(weekLayout);

    // Day Based

    QHBoxLayout *dayLayout = new QHBoxLayout();
    dayLayout->setMargin(0);

    QSpacerItem *dayLeftSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    dayLayout->addItem(dayLeftSpacer);

    QPushButton *prevDay = new QPushButton(QIcon("leftarrow.png"), "");
    dayLayout->addWidget(prevDay);

    daySpin = new QSpinBox();
    daySpin->setValue(3);
    daySpin->setMinimum(1);
    daySpin->setMaximum(14);
    daySpin->setSingleStep(1);
    daySpin->setFont(QFont("Arial", 18, QFont::Normal));    

    dayLayout->addWidget(daySpin);

    QPushButton *nextDay = new QPushButton(QIcon("rightarrow.png"), "");
    dayLayout->addWidget(nextDay);

    QSpacerItem *dayRightSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    dayLayout->addItem(dayRightSpacer);

    dayBasedWidget->setLayout(dayLayout);

    // Range based

    QHBoxLayout *rangeLayout = new QHBoxLayout();

    QSpacerItem *rangeLeftSpacer = new QSpacerItem(1,40,QSizePolicy::Expanding, QSizePolicy::Expanding);
    rangeLayout->addItem(rangeLeftSpacer);

    QPushButton *prevRange = new QPushButton(QIcon("leftarrow.png"), "");
    rangeLayout->addWidget(prevRange);

    QLabel *fromLabel = new QLabel(tr("From:"));
    rangeLayout->addWidget(fromLabel);

    start = new QDateEdit();
    start->setCalendarPopup(true);
    start->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    start->setFrame(false);
    start->setBackgroundRole(QPalette::NoRole);
    start->setFont(QFont("arial", 18));
    rangeLayout->addWidget(start);

    QLabel *toLabel = new QLabel(tr("To:"));
    rangeLayout->addWidget(toLabel);
    rangeLayout->setMargin(0);

    end = new QDateEdit();
    end->setCalendarPopup(true);
    end->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
    end->setFrame(false);
    end->setBackgroundRole(QPalette::NoRole);
    end->setFont(QFont("arial", 18));
    rangeLayout->addWidget(end);

    multiWeek = new QCheckBox();
    multiWeek->setChecked(false);
    rangeLayout->addWidget(multiWeek);

    QLabel *multiLabel = new QLabel(tr("Show full weeks"));
    rangeLayout->addWidget(multiLabel);

    QPushButton *nextRange = new QPushButton(QIcon("rightarrow.png"), "");
    rangeLayout->addWidget(nextRange);

    QSpacerItem *rangeRightSpacer = new QSpacerItem(1,1,QSizePolicy::Expanding, QSizePolicy::Expanding);
    rangeLayout->addItem(rangeRightSpacer);

    rangeBasedWidget->setLayout(rangeLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackedLayout);
    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));

    connect(monthCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onMonthChanged(int)));
    connect(yearCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(onYearChanged(int)));

    connect(prevMonth, SIGNAL(clicked()), this, SLOT(previous()));
    connect(nextMonth, SIGNAL(clicked()), this, SLOT(next()));

    connect(prevWeek, SIGNAL(clicked()), this, SLOT(previous()));
    connect(nextWeek, SIGNAL(clicked()), this, SLOT(next()));
    connect(weekSpin, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));

    connect(prevDay, SIGNAL(clicked()), this, SLOT(previous()));
    connect(nextDay, SIGNAL(clicked()), this, SLOT(next()));
    connect(daySpin, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));

    connect(prevRange, SIGNAL(clicked()), this, SLOT(previous()));
    connect(nextRange, SIGNAL(clicked()), this, SLOT(next()));

    connect(start, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateChanged(const QDate &)));
    connect(end, SIGNAL(dateChanged(const QDate &)), this, SLOT(dateChanged(const QDate &)));

    connect(multiWeek, SIGNAL(stateChanged(int)),
            this, SLOT(weekStateChanged(int)));
}

QSize SelectorWidget::sizeHint() const
{
    return QSize(50,50);
}

QSize SelectorWidget::minimumSizeHint() const
{
    return QSize(50,50);
}

int SelectorWidget::maximumHeight() const
{
    return 50;
}

QSize SelectorWidget::maximumSize() const 
{
    return QSize(50,50);
}
/*
QSizePolicy SelectorWidget::sizePolicy() const
{
    return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
*/

void SelectorWidget::setDate(QDate date)
{
    myDate = date;

    if(state == 0)
    {
        monthCombo->setCurrentIndex(myDate.month() -1);

        int index = 0;
        for (int year = myDate.year()-1; year <= myDate.year()+1; ++year)
        {
            yearCombo->setItemText(index, QString::number(year));
            yearCombo->setItemData(index, year);
            index++;
        }
        yearCombo->setCurrentIndex(1);

        emit monthChanged(myDate.year(), myDate.month());
    }else if(state == 1)
    {
        emit rangeChanged(myDate, myDate.addDays((7*weekSpin->value())-1));
    }else
    {
        emit rangeChanged(myDate, myDate.addDays(daySpin->value()-1));
    }
}

void SelectorWidget::onMonthChanged(int month)
{
    if(month+1 != myDate.month())
    {
        myDate.setDate(myDate.year(), month+1, 1);
        monthCombo->setCurrentIndex(month);
        emit monthChanged(myDate.year(), myDate.month());
    }
}

void SelectorWidget::onYearChanged(int year)
{
    year = yearCombo->itemData(year).toInt();

    if(year != myDate.year())
    {
        myDate.setDate(year, myDate.month(), 1);

        int index = 0;
        for (int year = myDate.year()-1; year <= myDate.year()+1; ++year)
        {
            yearCombo->setItemText(index, QString::number(year));
            yearCombo->setItemData(index, year);
            index++;
        }

        yearCombo->setCurrentIndex(1);
        emit monthChanged(myDate.year(), myDate.month());
    }
}

void SelectorWidget::previous()
{

    if(state == 0)
    {
        if(myDate.month() == 1)
        {
            myDate.setDate(myDate.year()-1, 12, 1);
            int index = 0;
            for (int year = myDate.year()-1; year <= myDate.year()+1; ++year)
            {
                yearCombo->setItemText(index, QString::number(year));
                yearCombo->setItemData(index, year);
                index++;
            }
            yearCombo->setCurrentIndex(1);
        }else
        {
            myDate.setDate(myDate.year(), myDate.month()-1, 1);
        }

        monthCombo->setCurrentIndex(myDate.month() - 1);

        emit monthChanged(myDate.year(), myDate.month());
    }else if(state == 1)
    {
        myDate = myDate.addDays(-7);
        emit rangeChanged(myDate, myDate.addDays((weekSpin->value() * 7) - 1));
    }else if(state == 2)
    {
        myDate = myDate.addDays(-1);
        emit rangeChanged(myDate, myDate.addDays(daySpin->value() - 1));
    }else
    {
        start->setDate(start->date().addDays(-1));
        end->setDate(end->date().addDays(-1));
    }
}

void SelectorWidget::next()
{
    if(state == 0)
    {
        if(myDate.month() == 12)
        {
            myDate.setDate(myDate.year()+1, 1, 1);

            int index = 0;
            for (int year = myDate.year()-1; year <= myDate.year()+1; ++year)
            {
                yearCombo->setItemText(index, QString::number(year));
                yearCombo->setItemData(index, year);
                index++;
            }
            yearCombo->setCurrentIndex(1);
        }else
        {
            myDate.setDate(myDate.year(), myDate.month()+1, 1);
        }

        monthCombo->setCurrentIndex(myDate.month() - 1);

        emit monthChanged(myDate.year(), myDate.month());
    }else if(state == 1)
    {
        myDate = myDate.addDays(7);
        emit rangeChanged(myDate, myDate.addDays((weekSpin->value() * 7) - 1));
    }else if(state == 2)
    {
        myDate = myDate.addDays(1);
        emit rangeChanged(myDate, myDate.addDays(daySpin->value() - 1));
    }else
    {
        start->setDate(start->date().addDays(1));
        end->setDate(end->date().addDays(1));
    }
}

void SelectorWidget::valueChanged(int i)
{
    if(state == 1)
    {        
        emit rangeChanged(myDate, myDate.addDays((7 * i)-1));
    }else
    {
        emit rangeChanged(myDate, myDate.addDays(i-1));
    }
}

void SelectorWidget::showMonthBased()
{    
    state = 0;
    stackedLayout->setCurrentIndex(state);

    monthCombo->setCurrentIndex(myDate.month() - 1);

    int index = 0;
    for (int year = myDate.year()-1; year <= myDate.year()+1; ++year)
    {
        yearCombo->setItemText(index, QString::number(year));
        yearCombo->setItemData(index, year);
        index++;
    }
    yearCombo->setCurrentIndex(1);

    emit modeChanged(0);
    emit monthChanged(myDate.year(), myDate.month());
}

void SelectorWidget::showWeekBased()
{
    state = 1;
    stackedLayout->setCurrentIndex(state);
    myDate = myDate.addDays(-(myDate.dayOfWeek()-1));
    emit modeChanged(0);
    emit rangeChanged(myDate, myDate.addDays((7*weekSpin->value())-1));
}

void SelectorWidget::showDayBased()
{
    state = 2;
    stackedLayout->setCurrentIndex(state);
    emit modeChanged(1);
    emit rangeChanged(myDate, myDate.addDays(daySpin->value()-1));
}

void SelectorWidget::showRangeBased()
{
    state = 3;
    stackedLayout->setCurrentIndex(state);
    start->setDate(myDate);
    end->setDate(myDate.addDays(2));

    if(multiWeek->isChecked())
        emit modeChanged(0);
    else
        emit modeChanged(1);

    emit rangeChanged(myDate, end->date());
}

void SelectorWidget::dateChanged(const QDate &date)
{
    if(end->date() < start->date())
        end->setDate(start->date());

    myDate = start->date();

    emit rangeChanged(myDate, end->date());
}

void SelectorWidget::weekStateChanged(int state)
{
    if(state == Qt::Checked)
        emit modeChanged(0);
    else
        emit modeChanged(1);
}
