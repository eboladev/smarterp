#ifndef ALLADVANCES_H
#define ALLADVANCES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class AllAdvances;
}


class Advances;
class CashAdvances;

class AllAdvances : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AllAdvances(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~AllAdvances();
    
private:
    Ui::AllAdvances *ui;

    Advances *m_advances;
    CashAdvances *m_cashAdvances;

    QSqlDatabase db;
};

#endif // ALLADVANCES_H
