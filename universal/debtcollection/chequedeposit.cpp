#include "chequedeposit.h"
#include "ui_chequedeposit.h"


#include "datapublics.h"
ChequeDeposit::ChequeDeposit(QWidget *parent, QSqlDatabase database, QString ID) :
    QDialog(parent),
    ui(new Ui::ChequeDeposit)
{
    ui->setupUi(this);
    db = database;
    chequeID = ID;

    ui->dtpDateDeposited->setDate(QDate::currentDate());

}

ChequeDeposit::~ChequeDeposit()
{
    delete ui;
}

void ChequeDeposit::on_cmdDeposit_clicked()
{
    bool OK = true;
    QString err = "";
    for (int i = 0; i < chequeIDs.count(); i++) {
        QSqlQuery qu = db.exec("UPDATE cheques SET "
                              " DepositedTo = '" + ui->cboPrime->currentText() + "', "
                             " DepositedOn = '" + ui->dtpDateDeposited->date().toString("yyyy-MM-dd") + "', "
                               " Comments = '" + ui->txtComment->toPlainText() + "' "
                                " WHERE ChequeID = '" + chequeIDs.at(i) + "'");
        if (qu.lastError().isValid()) {
            OK = false;
            err += qu.lastError().text() + "\n";
        }
    }
    if (OK) {
        this->accept();
    } else {
        DataPublics::showWarning(err);
    }
}

void ChequeDeposit::addCheque(QString chequeNo)
{
    chequeIDs.append(chequeNo);

    QSqlQuery qu = db.exec("SELECT * FROM cheques WHERE ChequeID = '" + chequeNo + "'");
    qu.first();
    QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstCheques);
    it->setText(0, qu.record().value("CustomerID").toString());
    it->setText(1, qu.record().value("Amount").toString());
    it->setText(2, qu.record().value("DateReceived").toDate().toString("dd MMM yyyy"));
}

