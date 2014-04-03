#ifndef MEMBERS_H
#define MEMBERS_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Members;
}

class Members : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Members(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Members();
private slots:
    void reloadList();
private:
    Ui::Members *ui;
    QSqlDatabase db;
};

#endif // MEMBERS_H
