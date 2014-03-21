#ifndef PAYROLLSUBCONTAINER_H
#define PAYROLLSUBCONTAINER_H

#include <QMainWindow>
#include <QtSql>
class Payslips;
class Payslips2;
class AllAdvances;
class LeaveDaysMW;
class Payroll;
namespace Ui {
class PayrollSubContainer;
}

class PayrollSubContainer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PayrollSubContainer(QWidget *parent = 0,
                                 QSqlDatabase database = QSqlDatabase(),
                                 bool payroll = false
                                 );
    ~PayrollSubContainer();
    
private:
    Ui::PayrollSubContainer *ui;
    QSqlDatabase db;
    bool canAccessPayroll;
    Payroll *m_payroll;
    Payslips2 *m_payslips;
    AllAdvances *m_advances;
    LeaveDaysMW *m_leave_days;
};

#endif // PAYROLLSUBCONTAINER_H
