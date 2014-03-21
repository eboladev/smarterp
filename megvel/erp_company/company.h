#ifndef COMPANY_H
#define COMPANY_H
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
namespace Ui {
class Company;
}

class Users;
class SalesReps;
class DataManager;

#include <QMainWindow>

class Company : public QMainWindow
{
    Q_OBJECT

public:
    explicit Company(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Company();
public slots:
    void reload();
private slots:
    void on_actionView_Edit_User_Roles_triggered();
private:
    Ui::Company *ui;
    QSqlDatabase db;

    Users *t_users;
    SalesReps *t_reps;
    DataManager *t_dataman;
};

#endif // COMPANY_H
