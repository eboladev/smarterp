#include "producteditoc.h"
#include "ui_producteditoc.h"

ProductEditOC::ProductEditOC(QWidget *parent, QSqlDatabase database, QString ocNo) :
	QDialog(parent),
	ui(new Ui::ProductEditOC)
{
	ui->setupUi(this);
	db = database;
	currentID = ocNo;
	getDetails();
}

ProductEditOC::~ProductEditOC()
{
	delete ui;
}

void ProductEditOC::getDetails()
{
	QSqlQuery qu = db.exec("SELECT * FROM newreport WHERE TicketNo = '" + currentID + "'");
	if (!qu.lastError().isValid()) {
		qu.first();
		ui->TicketNo->setText(qu.record().value("TicketNo").toString());
		ui->Qty->setText(qu.record().value("Qty").toString());
		ui->Customer->setText(qu.record().value("Client").toString());
		ui->Product->setText(qu.record().value("Product").toString());
		ui->PaperSpec->setText(qu.record().value("PaperSpecs").toString());

		QSqlRecord rec = qu.record();
		ui->A->setText(rec.value("A").toString());
		ui->F1->setText(rec.value("F1").toString());
		ui->L->setText(rec.value("L").toString());
		ui->F2->setText(rec.value("F2").toString());
		ui->F3->setText(rec.value("F3").toString());
		ui->S->setText(rec.value("S").toString());
		ui->T->setText(rec.value("T").toString());
		ui->W->setText(rec.value("W").toString());
	}
	QString spec = ui->PaperSpec->text();
	QStringList specDetails = spec.split("/");
	int type = specDetails.count();
	for (int i = 0; i < type; i++) {
		QString specAll = specDetails.at(i).trimmed();
		QString size = specAll.left(3);
		QString type = specAll.right(specAll.length() - 3);
		//qDebug() << size << type << specAll;

		if (i == 0) {
			ui->gram1->setText(size);
			ui->type1->setEditText(type);
		} else if (i == 1) {
			ui->gram2->setText(size);
			ui->type2->setEditText(type);
		} else if (i == 2) {
			ui->gram3->setText(size);
			ui->type3->setEditText(type);
		} else if (i == 3) {
			ui->gram4->setText(size);
			ui->type4->setEditText(type);
		} else if (i == 4) {
			ui->gram5->setText(size);
			ui->type5->setEditText(type);
		}
	}
	bool enable45 = true;
	if (type < 4)
		enable45 = false;

	ui->gram4->setEnabled(enable45);
	ui->type4->setEnabled(enable45);
	ui->type5->setEnabled(enable45);
	ui->gram5->setEnabled(enable45);
	ui->W5->setEnabled(enable45);
	ui->W4->setEnabled(enable45);
}

void ProductEditOC::on_cmdSave_clicked()
{

}
