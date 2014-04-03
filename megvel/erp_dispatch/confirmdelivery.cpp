#include "confirmdelivery.h"
#include "ui_confirmdelivery.h"
#include "datapublics.h"
ConfirmDelivery::ConfirmDelivery(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::ConfirmDelivery)
{
	ui->setupUi(this);
	db = database;
	reloadList();
}

ConfirmDelivery::~ConfirmDelivery()
{
	delete ui;
}

void ConfirmDelivery::on_cmdConfirm_clicked()
{
	int checked = 0;
	for (int i = 0; i < ui->trvDispatch->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->trvDispatch->invisibleRootItem()->child(i);
		if (it->checkState(0) == Qt::Checked) {
			checked ++;
			QString dispatchID = it->text(99);
			QString query = "INSERT INTO delivery (dispatchID, Date, Comment, ConfirmedBy, UserID) VALUES ('"
					+ dispatchID + "', "
					+ "Current_Date(), '"
					+ ui->txtComment->toPlainText() + "', '"
					+ DataPublics::getCurrentUserName(db) + "', '"
					+ DataPublics::getCurrentUserID() + "')";

			db.exec(query);
			if (db.lastError().isValid()) {
				DataPublics::showWarning(db.lastError().text());
				return;
			}

			query = "UPDATE dispatch set deliveryconfirmed = 'Yes' WHERE dispatchid = '" + dispatchID + "'";
			db.exec(query);
			if (db.lastError().isValid()) {
				DataPublics::showWarning(db.lastError().text());
				return;
			}
			DataPublics::logAuditTrail("Dispatch", "Deliveries confirmed.", db);
		}
	}
	if (checked < 1) {
		DataPublics::showWarning("No dispatch checked.");
		return;
	} else {
		reloadList();
	}
}

void ConfirmDelivery::reloadList()
{
	QSqlQuery qu = db.exec("SELECT dispatchid AS `ID`, invoiceNumber, dispatch.Date"
			       ", JobTicketNumber, newreport.Client, newreport.Product, QtyDispatched FROM dispatch, newreport WHERE deliveryConfirmed = 'No' AND dispatch.JobTicketNumber = newreport.TicketNo ORDER BY invoiceNumber ASC");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	}
	ui->trvDispatch->invisibleRootItem()->takeChildren();
	while (qu.next()) {
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->trvDispatch->invisibleRootItem());
		it->setText(99, qu.record().value("ID").toString());
		it->setText(0, qu.record().value("invoiceNumber").toString());
		it->setCheckState(0, Qt::Unchecked);
		it->setText(1, qu.record().value("Date").toString());
		it->setText(2, qu.record().value("JobTicketNumber").toString());
		it->setText(3, qu.record().value("Client").toString());
		it->setText(4, qu.record().value("Product").toString());
		it->setText(5, qu.record().value("QtyDispatched").toString());
	}
}
