#include "leaves.h"
#include "ui_leaves.h"
#include "leaveallocationeditor.h"
#include "leaveeditor.h"

Leaves::Leaves(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Leaves)
{
    ui->setupUi(this);



}

Leaves::~Leaves()
{
    delete ui;
}


