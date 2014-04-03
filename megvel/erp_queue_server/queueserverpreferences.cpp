#include "queueserverpreferences.h"
#include "ui_queueserverpreferences.h"

QueueServerPreferences::QueueServerPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueueServerPreferences)
{
    ui->setupUi(this);
}

QueueServerPreferences::~QueueServerPreferences()
{
    delete ui;
}
