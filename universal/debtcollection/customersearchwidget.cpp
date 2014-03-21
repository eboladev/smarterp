#include "customersearchwidget.h"
#include "ui_customersearchwidget.h"

customerSearchWidget::customerSearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customerSearchWidget)
{
    ui->setupUi(this);
}

customerSearchWidget::~customerSearchWidget()
{
    delete ui;
}
