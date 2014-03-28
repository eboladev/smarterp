#include "salesreps.h"
#include "ui_salesreps.h"
#include "salesrepeditor.h"
SalesReps::SalesReps(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::SalesReps)
{
    ui->setupUi(this);
    db = database;
    reload();
}

SalesReps::~SalesReps()
{
    delete ui;
}

void SalesReps::reload()
{
    ui->treeView->setQuery("SELECT * FROM vw_salesreps", db, "Sales Representatives", true);
    ui->treeView->setColumnHidden(0, true);
}

void SalesReps::on_treeView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id = ui->treeView->getCurrentID();
    SalesRepEditor *rep = new SalesRepEditor(this, db);
    rep->currentId = id;
    rep->edit();
    if (rep->exec()) {
        reload();
    }
}

void SalesReps::on_cmdAddNew_clicked()
{
    SalesRepEditor *rep = new SalesRepEditor(this, db);
    rep->addNew();
    if (rep->exec()) {
        reload();
    }
}
