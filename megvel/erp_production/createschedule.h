#ifndef CREATESCHEDULE_H
#define CREATESCHEDULE_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class CreateSchedule;
}

class CreateSchedule : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CreateSchedule(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CreateSchedule();
    
private slots:
    void reloadOrderList(QDate newDate);
    void reloadSchedule();
    void on_cmdPrintSchedule_clicked();

    void on_cmdAddToSchedule_clicked();

    void on_cmdRemoveFromSchedule_clicked();

    void on_trvSchedule_doubleClicked(const QModelIndex &index);

    void on_cmdSaveSchedule_clicked();

private:
    Ui::CreateSchedule *ui;
    QSqlDatabase db;
};

#endif // CREATESCHEDULE_H
