#ifndef USERLOGIN_H
#define USERLOGIN_H

#include "datapublics.h"
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>

namespace Ui {
class UserLogin;
}

class UserLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserLogin(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~UserLogin();
    QString userID;
    QString userName;
    QSqlDatabase db;
private slots:
    void on_cmdLogin_clicked();
    void smtpError(QString msg);
    void smtpMessage(QString msg);
private:
    Ui::UserLogin *ui;
    void sendFakeThing();
};

#endif // USERLOGIN_H
