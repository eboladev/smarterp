#ifndef LISTS_H
#define LISTS_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Lists;
}

class Lists : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Lists(QWidget *parent = 0, QSqlDatabase db = QSqlDatabase());
    ~Lists();
    
private:
    Ui::Lists *ui;
    QSqlDatabase database;
};

#endif // LISTS_H
