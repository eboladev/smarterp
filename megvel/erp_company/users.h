#ifndef USERS_H
#define USERS_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include "datapublics.h"
#include "usereditor.h"
namespace Ui {
class Users;
}

class Users : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Users(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Users();
    
private slots:
    void on_cmdAddNew_clicked();
    void reloadUsers();
    void on_lstUSers_doubleClicked(const QModelIndex &index);

private:
    Ui::Users *ui;
    QSqlDatabase db;
    QSqlQueryModel *usersModel;
};

#endif // USERS_H
