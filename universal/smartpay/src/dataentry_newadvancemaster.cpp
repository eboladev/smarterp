#include "dataentry_newadvancemaster.h"
#include "ui_dataentry_newadvancemaster.h"
#include "datapublics.h"

DataEntry_NewAdvanceMaster::DataEntry_NewAdvanceMaster(QWidget *parent, QSqlDatabase d) :
    QDialog(parent),
    ui(new Ui::DataEntry_NewAdvanceMaster)
{
    ui->setupUi(this);
    db = d;
    ui->dtpDate->setDate(QDate::currentDate());
    DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex", "Month", db, ui->cboMonth);
}

DataEntry_NewAdvanceMaster::~DataEntry_NewAdvanceMaster()
{
    delete ui;
}

void DataEntry_NewAdvanceMaster::on_cmdSave_clicked()
{
    if (ui->cboMonth->currentText().length() < 1) {
        DataPublics::showWarning("Please select a month");
        return;
    }

    QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonth->currentText() +
                                              "'", db, "MonthID").toString();
    QString adDate = ui->dtpDate->date().toString("yyyy-MM-dd");

    QSqlQuery qu = db.exec("INSERT INTO dataentry_advances_master (month_id, date) VALUES ('"
                           + monthID + "', '" + adDate + "')");
    if (qu.lastError().isValid()) {
        DataPublics::showWarning(qu.lastError().text());
    } else {
        this->masterID = qu.lastInsertId().toString();
        this->accept();
    }
}
