#include "reelallocationeditor.h"
#include "ui_reelallocationeditor.h"
#include "datapublics.h"

ReelAllocationEditor::ReelAllocationEditor(QWidget *parent, QSqlDatabase database) :
	QDialog(parent),
	ui(new Ui::ReelAllocationEditor)
{
	ui->setupUi(this);
	db = database;
}

ReelAllocationEditor::~ReelAllocationEditor()
{
	delete ui;
}

void ReelAllocationEditor::on_cmdSave_clicked()
{
	QString reelID = DataPublics::getDbValue("SELECT * FROM reels WHERE ReelNumber = '" + ui->txtReelNo->text() + "'", db, "ReelID").toString();
	QString ocID = DataPublics::getDbValue("SELECT * FROM newreport WHERE TicketNo = '" + ui->txtOCNo->text() + "'", db, "EntryID").toString();

	if (reelID.length() < 1) {
		DataPublics::showWarning("Reel Not Found");
		return;
	}

	if (ocID.length() < 1) {
		DataPublics::showWarning("OC Not Found");
		return;
	}

	QSqlQuery qu = db.exec("INSERT INTO reel_allocation (ReelID, OCID, Section) VALUES ('" +
			       reelID + "', '" +
			       ocID + "', '" + ui->txtSection->text() + "')");
	if (qu.lastError().isValid()) {
		DataPublics::showWarning(qu.lastError().text());
		return;
	} else {
		this->accept();
	}
}
