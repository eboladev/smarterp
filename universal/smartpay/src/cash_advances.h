#ifndef CashAdvances_H
#define CashAdvances_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class CashAdvances;
}

class CashAdvances : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CashAdvances(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CashAdvances();
    
private slots:

    void on_cboMonths_currentIndexChanged(const QString &arg1);

    void on_actionNew_Advance_triggered();

    void on_cmdDelete_clicked();

    void on_actionRefresh_triggered();

private:
    Ui::CashAdvances *ui;
    QSqlDatabase db;
};

#endif // CashAdvances_H
