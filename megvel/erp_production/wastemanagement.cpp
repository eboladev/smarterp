#include "wastemanagement.h"
#include "ui_wastemanagement.h"

WasteManagement::WasteManagement(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::WasteManagement)
{
    ui->setupUi(this);
    db = database;
    ui->dtpStart->setDate(QDate::currentDate().addDays(-30));
    ui->dtpEnd->setDate(QDate::currentDate());
    on_cmdRefresh_clicked();
}

WasteManagement::~WasteManagement()
{
    delete ui;
}

void WasteManagement::on_cmdRefresh_clicked()
{
    ui->trvWaste->setQuery("SELECT * FROM vw_corrugator_waste WHERE Date BETWEEN '" + ui->dtpStart->date().toString("yyyy-MM-dd")
                           + "' AND '" + ui->dtpEnd->date().toString("yyyy-MM-dd") + "'", db, "Corrugator Waste", true);
    ui->trvWaste->setColumnHidden(0, true);
}

#include "wastedataentry.h"
void WasteManagement::on_actionNew_Entry_triggered()
{
    WasteDataEntry *dt = new WasteDataEntry(this, db);
    if (dt->exec() == QDialog::Accepted)
        on_cmdRefresh_clicked();
}

void WasteManagement::on_trvWaste_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id =  ui->trvWaste->getCurrentID();
    WasteDataEntry *ed = new WasteDataEntry(this, db);
    ed->currentID = id;
    ed->isAdding = false;
    ed->edit();
    if (ed->exec() == QDialog::Accepted) {
        on_cmdRefresh_clicked();
    }
}
