#include "transactionview.h"
#include "ui_transactionview.h"

TransactionView::TransactionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionView)
{
    ui->setupUi(this);

    reInitialize();
}

TransactionView::~TransactionView()
{
    delete ui;
}

void TransactionView::setCustomer(QString c)
{
    m_customer = c;
    for (int i = 0; i < ui->cboCustomers->count(); i++) {
        if (ui->cboCustomers->itemText(i) == c)
            ui->cboCustomers->setCurrentIndex(i);
    }
}

void TransactionView::setCustomerID(QString cID)
{
    m_customer = cID;
}

void TransactionView::setStartDate(QDate d)
{
    m_startDate = d;
    ui->dtpStartDate->setDate(d);
}

void TransactionView::setEndDate(QDate d)
{
    m_endDate = d;
    ui->dtpEndDate->setDate(d);
}

void TransactionView::setTxnType(QString t)
{
    m_type = t;
    for (int i = 0; i < ui->cboTxnType->count(); i++) {
        if (ui->cboTxnType->itemText(i) == t)
            ui->cboTxnType->setCurrentIndex(i);
    }
}

void TransactionView::reloadData()
{
    transModel = new TransactionsModel(this);
    QString txnWhere = " AND (TxnType LIKE '%%') ";
    if (ui->cboTxnType->currentText() != "All") {
        txnWhere = " AND (TxnType LIKE '%" + ui->cboTxnType->currentText() + "%') ";
    }

    QString custWhere = " AND (TxnCustomer LIKE '%%') ";

    if (ui->cboCustomers->currentText() != "All") {
        custWhere = " AND (TxnCustomer = '" + ui->cboCustomers->currentText() + "') ";
    }

    QString query = "SELECT * FROM transactions WHERE `NewDate` BETWEEN '" + m_startDate.toString("yyyy-MM-dd") + "' AND '" + m_endDate.toString("yyyy-MM-dd") + "' " + txnWhere + custWhere;
    transModel->setQuery(query, Publics::getDatabase());
    qDebug() << query;
    ui->trvData->setModel(transModel);
    ui->trvData->setColumnHidden(0, true);
    ui->trvData->setColumnHidden(8, true);
    ui->trvData->setColumnHidden(9, true);
}

void TransactionView::reInitialize()
{
    ui->cboCustomers->clear();
    ui->cboCustomers->addItem("All");
    Publics::loadDbToComboBox(Publics::getDatabase(), ui->cboCustomers, "SELECT Distinct(TxnCustomer) FROM transactions", "TxnCustomer");

    setCustomer("All");
    setStartDate(QDate::currentDate().addDays(-90));
    setEndDate(QDate::currentDate());
    setTxnType("All");

    reloadData();
}

void TransactionView::on_cboCustomers_textChanged(const QString &arg1)
{
    setCustomer(arg1);
    reloadData();
}

void TransactionView::on_dtpStartDate_dateChanged(const QDate &date)
{
    setStartDate(date);
    reloadData();
}

void TransactionView::on_dtpEndDate_dateChanged(const QDate &date)
{
    setEndDate(date);
    reloadData();
}

void TransactionView::on_cboTxnType_currentIndexChanged(const QString &arg1)
{
    setTxnType(arg1);
    reloadData();
}
