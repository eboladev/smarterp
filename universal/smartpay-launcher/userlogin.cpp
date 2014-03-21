#include "userlogin.h"
#include "ui_userlogin.h"

UserLogin::UserLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
}

UserLogin::~UserLogin()
{
    delete ui;
}
