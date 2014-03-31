#ifndef DCMAINWINDOW_H
#define DCMAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QSqlDatabase>

#include "customersearchwidget.h"
#include <QModelIndex>
#include "quickcalendarview.h"
#include "selectorwidget.h"
#include "calendar.h"
#include "calendartablemodel.h"
#include <QTableView>
#include <QTreeWidgetItem>
class AgeingModel;

namespace Ui {
    class DCMainWindow;
}

class DCMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DCMainWindow(QWidget *parent = 0);
    ~DCMainWindow();
    
private slots:
    void on_actionNew_Action_triggered();
    void reloadCalendarSpecs();
    void reloadCalendar();
    void on_actionNew_File_triggered();
    void reloadFiles();
    void loadFile(QString fileNo);
    void on_cmdDateLeft_clicked();

    void on_cmdDateRight_clicked();



    void on_actionAction_Types_triggered();

    void on_actionNew_Appointment_triggered();
    void SaveNewAppointment(Appointment *app);

    void reloadTransactions();
    void reloadAgeing();

    void on_actionNew_Call_triggered();

    void on_trvAgeing_doubleClicked(const QModelIndex &index);

    void on_cboCalendarMode_currentIndexChanged(const QString &arg1);

    void on_actionView_Register_triggered();
    void reloadCheques();
    void on_cmdNewCheque_clicked();

    void on_lstCheques_doubleClicked(const QModelIndex &index);

    void on_cmdDeposit_clicked();

    void on_cmdRefreshAgeing_clicked();

    void on_trvChequeList_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_dtpChequeDate_dateChanged(const QDate &date);

private:
    QSettings *sett;
    Ui::DCMainWindow *ui;
    QSqlDatabase db;

    customerSearchWidget *m_customerSearchWidget;
    bool hasFile;
    QString currentFileNo;

    QList <QColor> myColors;
    QList <QIcon> myIcons;

    QuickCalendarView *ptrCalendarView;
    SelectorWidget *ptrSelectorWidget;
    QTableView *ptrTableView;
    CalendarTableModel *ptrCalendarModel;

    QList <Calendar *> myCalendars;


    QDate calStartDate;

    int runCount;
    AgeingModel *ageingModel;
};

#endif // DCMAINWINDOW_H
