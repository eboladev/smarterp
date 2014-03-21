#include "lists.h"
#include "ui_lists.h"

Lists::Lists(QWidget *parent, QSqlDatabase db) :
    QMainWindow(parent),
    ui(new Ui::Lists)
{
    ui->setupUi(this);
    database = db;
}

Lists::~Lists()
{
    delete ui;
}
