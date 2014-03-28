#ifndef AUTOCLOCKIN_H
#define AUTOCLOCKIN_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AutoClockIn;
}

class AutoClockIn : public QDialog
{
    Q_OBJECT
    
public:
    explicit AutoClockIn(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~AutoClockIn();
    
private:
    Ui::AutoClockIn *ui;
    QSqlDatabase db;

    void reloadEmployees();
    QSqlQueryModel *employeesModel;
};

#endif // AUTOCLOCKIN_H
