#ifndef OVERTIME_H
#define OVERTIME_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Overtime;
}

class Overtime : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Overtime(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Overtime();
    
private slots:
    void scanMonth();
    void on_cboMonths_currentIndexChanged(int index);
    void reloadTable();
    void on_cmdAddNew_clicked();

    void on_cmdSave_clicked();

private:
    Ui::Overtime *ui;
    QSqlDatabase db;

    QString currentMonth;

    QSqlRelationalTableModel *otModel;
    QSqlTableModel *employeesModel;
    QSqlTableModel *monthsModel;
};

#endif // OVERTIME_H
