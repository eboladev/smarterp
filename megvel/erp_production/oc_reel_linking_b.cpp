#include "oc_reel_linking_b.h"
#include "ui_oc_reel_linking_b.h"
#include "datapublics.h"
oc_reel_linking_b::oc_reel_linking_b(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::oc_reel_linking_b)
{
    ui->setupUi(this);
    db = database;

    //ui->lstReels->setQuery("SELECT ReelID, ReelNumber, Supplier, Size, Type, GSM, Balance FROM reels", db, "Reels", true);
    //ui->lstReels->setColumnHidden(0, true);

    ui->dtpProductionDate->setDate(QDate::currentDate().addDays(-1));
    on_dtpProductionDate_dateChanged(QDate::currentDate().addDays(-1));
}

oc_reel_linking_b::~oc_reel_linking_b()
{
    delete ui;
}

void oc_reel_linking_b::on_dtpProductionDate_dateChanged(const QDate &date)
{
    QString query = "";
    query = "SELECT TicketNo, Client, Product, PaperSpecs as 'P/Spec' FROM newreport WHERE ScheduleDate = '" + date.toString("yyyy-MM-dd") + "'";
    ui->lstAllOCs->setQuery(query, db, "Orders", false);
}

void oc_reel_linking_b::on_lstAllOCs_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);

    QString ocNo = ui->lstAllOCs->getCurrentID();
    QString reelID = DataPublics::getDbValue("SELECT ReelID FROM reels Where ReelNumber = '" + ui->txtReelNo->text() + "'", db, "ReelID").toString();

    if (reelID.length() < 1 || ocNo.length() < 1) {
        DataPublics::showWarning("Select an OC and a reel");
        return;
    }

    QString productionDate = ui->dtpProductionDate->date().toString("yyyy-MM-dd");
    QString reelNo = ui->txtReelNo->text(); //DataPublics::getDbValue("SELECT ReelNumber FROM reels WHERE ReelID = '" + reelID + "'", db, "ReelNumber").toString();


    QSqlQuery qu = db.exec("INSERT INTO production_allocated_ocs (ProductionDate, "
                           "ReelID, ReelNo, Section, OcNo) VALUES ('"
                           + productionDate + "', '" +
                           reelID  + "', '" +
                           reelNo  + "', '" +
                           ui->txtSection->text() + "', '" +
                           ocNo + "')");

    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
        return;
    }

    reloadSelectedOcs();
}

void oc_reel_linking_b::reloadSelectedOcs()
{
    ui->lstSelectedOCs->setQuery("SELECT EntryID, OCNo FROM production_allocated_ocs WHERE ReelNo = '" + ui->txtReelNo->text() + "' AND ProductionDate = '" + ui->dtpProductionDate->date().toString("yyyy-MM-dd") + "'", db, "Selected Orders", true );
    ui->lstSelectedOCs->setColumnHidden(0, true);
}

void oc_reel_linking_b::on_txtReelNo_returnPressed()
{
    reloadSelectedOcs();
}

void oc_reel_linking_b::on_pushButton_clicked()
{

}
