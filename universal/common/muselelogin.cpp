#include "muselelogin.h"
#include "ui_muselelogin.h"
#include "dbtools.h"
MuseleLogin::MuseleLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MuseleLogin)
{
    ui->setupUi(this);
}

MuseleLogin::~MuseleLogin()
{
    delete ui;
}

void MuseleLogin::on__login_clicked()
{
    databaseURL = "mysql://" + ui->_server->text() + ":3306/" + ui->_database->text();
    QSqlDatabase db = databaseFromURL(databaseURL);
    db.setUserName(ui->_username->text());
    db.setPassword(ui->_password->text());
    this->accept();
}

void MuseleLogin::on__close_clicked()
{
    this->reject();
}
