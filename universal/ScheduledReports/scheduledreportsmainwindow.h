#ifndef SCHEDULEDREPORTSMAINWINDOW_H
#define SCHEDULEDREPORTSMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QPrinter>

namespace Ui {
class ScheduledReportsMainWindow;
}

class ScheduledReportsMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ScheduledReportsMainWindow(QWidget *parent = 0);
    ~ScheduledReportsMainWindow();
    
private:
    Ui::ScheduledReportsMainWindow *ui;
    QSqlDatabase db;

private slots:
    void reloadReportList();
    void on_action_New_triggered();
    void on_trvReports_doubleClicked(const QModelIndex &index);
    void on_action_Print_Preview_triggered();
};

#endif // SCHEDULEDREPORTSMAINWINDOW_H
