#ifndef FREEPAYROLLMW_H
#define FREEPAYROLLMW_H

#include <QMainWindow>
#include <QtSql>

#include <QLabel>
namespace Ui {
class FreePayrollMW;
}

class FreePayrollMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit FreePayrollMW(QWidget *parent = 0);
    ~FreePayrollMW();

private slots:
    void on_actionBasic_Info_triggered();
    void updateCompanyStatusLabelTexts();
    void on_actionBranches_triggered();

    void on_actionDepartments_triggered();

    void on_actionJob_Groups_triggered();

    void on_actionCo_operatives_triggered();

    void on_actionPension_Funds_triggered();

    void on_actionEmployee_triggered();

    void on_actionAbout_FreePayroll_triggered();

private:
    Ui::FreePayrollMW *ui;
    QSqlDatabase db;

    QLabel *connectionStatusLabel;
    QLabel *companyNameLabel;
    QLabel *currentMonthLabel;
};

#endif // FREEPAYROLLMW_H
