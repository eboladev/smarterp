#ifndef HR_LEAVES_H
#define HR_LEAVES_H

#include   <QtSql>
#include <QMainWindow>

namespace Ui {
class HR_Leaves;
}

class HR_Leaves : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit HR_Leaves(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~HR_Leaves();
    
private:
    Ui::HR_Leaves *ui;
    QSqlDatabase db;

private slots:
    void reloadEmployees();
};

#endif // HR_LEAVES_H
