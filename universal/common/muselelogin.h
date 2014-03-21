#ifndef MUSELELOGIN_H
#define MUSELELOGIN_H

#include <QDialog>

namespace Ui {
class MuseleLogin;
}

class MuseleLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit MuseleLogin(QWidget *parent = 0);
    ~MuseleLogin();
    QString databaseURL;
private slots:
    void on__login_clicked();

    void on__close_clicked();

private:
    Ui::MuseleLogin *ui;
};

#endif // MUSELELOGIN_H
