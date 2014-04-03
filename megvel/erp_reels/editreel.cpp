#include "editreel.h"
#include "ui_editreel.h"

#include <QFont>

EditReel::EditReel(QWidget *parent, QSqlDatabase database, QString reelID) :
	QDialog(parent),
	ui(new Ui::EditReel)
{
	ui->setupUi(this);
	db = database;
	currentID = reelID;

	QSqlQuery qu = db.exec("SELECT * FROM reels WHERE ReelID = '" + currentID + "'");
	if (qu.lastError().isValid()) {

	} else {
		qu.first();
		QSqlRecord rec = qu.record();
		ui->txtReelNumber->setText(rec.value("ReelNumber").toString());

		ui->barcodeWidget->reelNumber = rec.value("ReelNumber").toString();

	}
}

EditReel::~EditReel()
{
	delete ui;
}
