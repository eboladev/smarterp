#ifndef PAYROLL_H
#define PAYROLL_H

#include <QtGui>
#include <QtSql>
#include "customqueryview.h"
#include <QPrinter>

class PayrollReportPreview;

namespace Ui {
class Payroll;
}


class Payroll : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Payroll(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Payroll();
    
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Recalculate_clicked();
    void on_cmdClear_clicked();
    void calculatorProgress(int p);
    void calculatorFinished();
    void calculatorEmployee(QString e);
    void on_cmdShowP10A_clicked();
    void on_cmdShowP10D_clicked();
    void on_cmdShowP9A_clicked();
signals:
    void recalculated();
private:
    Ui::Payroll *ui;
    QSqlDatabase db;
    void reloadMonths();
    QSqlQueryModel *model;
    QSortFilterProxyModel *fModel;
    QString monthID;
    void loadPayroll();
    QString getReportXML(QString reportName, QString stringToReplace = "",
                         QString replaceMent = ""
            );
};

#endif // PAYROLL_H
