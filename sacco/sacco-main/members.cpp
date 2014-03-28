#include "members.h"
#include "ui_members.h"

Members::Members(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Members)
{
    ui->setupUi(this);
    db = database;
    reloadList();
}

Members::~Members()
{
    delete ui;
}

void Members::reloadList()
{

}
