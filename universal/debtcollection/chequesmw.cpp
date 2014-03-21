#include "chequesmw.h"
#include "ui_chequesmw.h"

ChequesMW::ChequesMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChequesMW)
{
    ui->setupUi(this);
}

ChequesMW::~ChequesMW()
{
    delete ui;
}
