#ifndef PAYROLLCONTAINER_H
#define PAYROLLCONTAINER_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class PayrollContainer;
}

class PayrollContainer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PayrollContainer(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), bool embedded = false);
    ~PayrollContainer();
    
private:
    Ui::PayrollContainer *ui;
    QSqlDatabase db;
    void logIn();
    bool bEmbed;
};

#endif // PAYROLLCONTAINER_H
