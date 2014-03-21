#include "makesaccopayment.h"
#include "ui_makesaccopayment.h"

MakeSaccoPayment::MakeSaccoPayment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MakeSaccoPayment)
{
    ui->setupUi(this);
}

MakeSaccoPayment::~MakeSaccoPayment()
{
    delete ui;
}
