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

#ifndef CALENDARDETAILSFORM_H
#define CALENDARDETAILSFORM_H

#include <QStringList>
#include <QTableView>
#include <QWidget>

#include "calendar.h"
#include "varianttablemodel.h"
#include "ui_calendardetailsform.h"

/*!
    \class CalendarDetailsForm
    \brief Form to edit details of calendars.
*/

class CalendarDetailsForm : public QWidget, public Ui::CalendarDetailsForm
{
    Q_OBJECT

public:
    CalendarDetailsForm(QWidget *parent = 0);

    bool saveChanges();
    void discardChanges();
    bool validate();

    bool isModified() const;

public slots:
    void setCalendar(const Calendar &calendar);

signals:
    void changesSaved(const Calendar &calendar);
    void changesDiscarded();
    void calendarDeleted(const Calendar &calendar);

private slots:
    void onSaveChanges();
    void onDiscardChanges();
    void onDeleteCalendar();
    void onMoveLeft(const QModelIndexList &indexes);
    void onMoveRight(const QModelIndexList &indexes);

private:
    void disable();

    QStringList myErrors;

    Calendar myCalendar;

    QTableView myLeftView;
    QTableView myRightView;

    VariantTableModel <Permission> mySelectedModel;
    VariantTableModel <Permission> myDatabaseModel;

    QList <Permission> mySelected;
    QList <Permission> myDatabase;
};

#endif
