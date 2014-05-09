#ifndef SCHEDULERMW_H
#define SCHEDULERMW_H

#include <QMainWindow>
#include <QDate>
namespace Ui {
class SchedulerMW;
}

class SchedulerMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit SchedulerMW(QWidget *parent = 0);
    ~SchedulerMW();

private slots:
    void on_calDate_clicked(const QDate &date);
    void reloadSchedule();
    void on_cmdAddOrder_clicked();

    void on_cmdDeleteFromSchedule_clicked();

    void on_cmdPrintSchedule_clicked();

private:
    Ui::SchedulerMW *ui;
};

#endif // SCHEDULERMW_H
