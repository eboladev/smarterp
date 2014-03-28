#include "mydock.h"
#include "ui_mydock.h"

MyDock::MyDock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDock)
{
    ui->setupUi(this);
}

MyDock::~MyDock()
{
    delete ui;
}
