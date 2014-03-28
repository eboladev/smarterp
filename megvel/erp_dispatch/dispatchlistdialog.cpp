#include "dispatchlistdialog.h"
#include "ui_dispatchlistdialog.h"

DispatchListDialog::DispatchListDialog(QWidget *parent, QString ticketNo, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::DispatchListDialog)
{
    ui->setupUi(this);
    ui->trvDispatches->setQuery("SELECT * FROM vw_alldispatch WHERE `Ticket No` = '" + ticketNo + "'", db, "Dispatches For Order No " + ticketNo , true);
    ui->trvDispatches->setColumnHidden(0, true);
}

DispatchListDialog::~DispatchListDialog()
{
    delete ui;
}
