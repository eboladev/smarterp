#include "reelallocation.h"
#include "ui_reelallocation.h"

ReelAllocation::ReelAllocation(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::ReelAllocation)
{
    ui->setupUi(this);
    db = database;
    reload();
}

ReelAllocation::~ReelAllocation()
{
    delete ui;
}

void ReelAllocation::reload()
{
    ui->treeView->setQuery("SELECT * FROM vw_reel_allocations", db, "Reel Allocations", true);
    ui->treeView->setColumnHidden(0, true);
}

#include "reelallocationeditor.h"
void ReelAllocation::on_actionNew_Entry_triggered()
{
    ReelAllocationEditor *ed = new ReelAllocationEditor(this, db);
    if (ed->exec() == QDialog::Accepted)
        reload();
}
