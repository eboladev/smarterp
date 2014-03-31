#include "hr_leaves.h"
#include "ui_hr_leaves.h"

HR_Leaves::HR_Leaves(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::HR_Leaves)
{
    ui->setupUi(this);
    db = database;
}

HR_Leaves::~HR_Leaves()
{
    delete ui;
}

void HR_Leaves::reloadEmployees()
{
//    ui->treeView->setQuery(
//                "SELECT * FROM vw_employeenames"
//                );
}
