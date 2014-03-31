#include "dataentry_advances.h"
#include "ui_dataentry_advances.h"
#include "datapublics.h"
DataEntry_Advances::DataEntry_Advances(QWidget *parent, QSqlDatabase d) :
    QMainWindow(parent),
    ui(new Ui::DataEntry_Advances)
{
    ui->setupUi(this);
    db = d;
    lockDataEntry(true);
    requeryMaster();
}

DataEntry_Advances::~DataEntry_Advances()
{
    delete ui;
}

void DataEntry_Advances::loadMaster(QString masterID)
{
    currentMasterID = masterID;

    ui->txtMasterDetails->setText("");

    QString html = "<h3>Advance Data Entry</h3><br/>";
    html += "<b>Date</b> " + masterQuery.record().value("date").toDate().toString("dd MMM yyyy");

    ui->txtMasterDetails->setHtml(html);


    lockDataEntry(false);
    advanceModel = new QSqlRelationalTableModel(this, db);
    advanceModel->setEditStrategy(QSqlRelationalTableModel::OnRowChange);
    advanceModel->setTable("dataentry_advances");
    advanceModel->setFilter("master_id = '" + currentMasterID + "'");

    QSqlRelation rel = QSqlRelation("vw_employeenames_ex", "employeeID", "Name");
    advanceModel->setRelation(2, rel);
    advanceModel->select();


    ui->tblAdvances->setModel(advanceModel);
    ui->tblAdvances->setColumnHidden(0, true);
    ui->tblAdvances->setItemDelegate(new QSqlRelationalDelegate(ui->tblAdvances));

    ui->tblAdvances->resizeColumnsToContents();
    ui->tblAdvances->resizeRowsToContents();
}

void DataEntry_Advances::lockDataEntry(bool locked)
{
    ui->cmdNewAdvance->setDisabled(locked);
    ui->cmdDeleteAdvance->setDisabled(locked);
    ui->cmdSave->setDisabled(locked);
    ui->tblAdvances->setDisabled(locked);
}

void DataEntry_Advances::requeryMaster()
{
    masterQuery = db.exec("SELECT * FROM dataentry_advances_master");
    if (masterQuery.lastError().isValid()) {
        DataPublics::showWarning(masterQuery.lastError().text());
        return;
    } else {
        QString max = QString::number(masterQuery.size());
        ui->lblPos->setText(max + "/" + max);
        if (masterQuery.size() > 0) {
            masterQuery.last();
            loadMaster(masterQuery.record().value("master_id").toString());
        }
    }
}

#include "dataentry_newadvancemaster.h"
void DataEntry_Advances::on_cmdNew_clicked()
{
    DataEntry_NewAdvanceMaster *newD = new DataEntry_NewAdvanceMaster(this, db);
    if (newD->exec()  == QDialog::Accepted  ) {
        //QString mID = newD->masterID;
        //loadMaster(mID);
        requeryMaster();
    }
}

void DataEntry_Advances::on_cmdPrevious_clicked()
{
    if (masterQuery.at() < 0) {
        DataPublics::showWarning("Invalid record location");
        return;
        masterQuery.first();
        loadMaster(masterQuery.record().value("master_id").toString());
    }

    if (masterQuery.at() > 0) {
        masterQuery.previous();
        loadMaster(masterQuery.record().value("master_id").toString());
        return;
    }

    if (masterQuery.at() == 0) {
        DataPublics::showWarning("End of list reached.");
        masterQuery.first();
        loadMaster(masterQuery.record().value("master_id").toString());
    }
}

void DataEntry_Advances::on_cmdNext_clicked()
{
    if (masterQuery.at() > masterQuery.size()) {
        DataPublics::showWarning("Invalid record location");
        return;
        masterQuery.last();
        loadMaster(masterQuery.record().value("master_id").toString());
    }

    if (masterQuery.at() < masterQuery.size()) {
        masterQuery.next();
        loadMaster(masterQuery.record().value("master_id").toString());
        return;
    }

    if (masterQuery.at() == masterQuery.size()) {
        DataPublics::showWarning("End of list reached.");
        masterQuery.last();
        loadMaster(masterQuery.record().value("master_id").toString());
    }
}

void DataEntry_Advances::on_cmdNewAdvance_clicked()
{
    int r = advanceModel->rowCount();
    advanceModel->insertRow(r);

    QModelIndex index = advanceModel->index(r, 1);
    advanceModel->setData(index, currentMasterID, Qt::EditRole);
    advanceModel->setData(index, currentMasterID, Qt::DisplayRole);

    ui->tblAdvances->resizeColumnsToContents();
    ui->tblAdvances->resizeRowsToContents();
}

void DataEntry_Advances::on_cmdDeleteAdvance_clicked()
{
    ui->tblAdvances->resizeColumnsToContents();
    ui->tblAdvances->resizeRowsToContents();
}

void DataEntry_Advances::on_cmdSave_clicked()
{
    advanceModel->submitAll();
}
