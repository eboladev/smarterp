#include "finishing_gluing.h"
#include "ui_finishing_gluing.h"

Finishing_Gluing::Finishing_Gluing(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Finishing_Gluing)
{
	ui->setupUi(this);
	db = database;
	ui->dtpDate->setDate(QDate::currentDate());
	on_dtpDate_dateChanged(ui->dtpDate->date());
}

Finishing_Gluing::~Finishing_Gluing()
{
	delete ui;
}


#include "finishing_dataentry.h"
void Finishing_Gluing::on_lstData_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	QString entryID = ui->lstData->getCurrentID();
	if (entryID.length() > 0) {
		Finishing_DataEntry *ent = new Finishing_DataEntry(this, db);
		ent->Edit(entryID);
		if (ent->exec() == QDialog::Accepted) {
			on_dtpDate_dateChanged(ui->dtpDate->date());
		}
	}
}

void Finishing_Gluing::on_actionNew_Entry_triggered()
{
	Finishing_DataEntry *ent = new Finishing_DataEntry(this, db);
	ent->AddNew("Gluing", ui->dtpDate->date());
	if (ent->exec() == QDialog::Accepted) {
		on_dtpDate_dateChanged(ui->dtpDate->date());
	}
}

void Finishing_Gluing::on_dtpDate_dateChanged(const QDate &date)
{
	ui->lstData->setQuery("SELECT * FROM vw_finishing WHERE Section LIKE '%Glu%' AND Date = '" + date.toString("yyyy-MM-dd") + "'", db, "Finishing Sectiong - Gluing", true);
	ui->lstData->setColumnHidden(0, true);
}

void Finishing_Gluing::on_cmdDelete_clicked()
{
	if (ui->lstData->getCurrentID().length() > 0) {
		if (QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this entry?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("UPDATE finishingdataentry SET Deleted = 'Yes' AND DateDeleted = CURRENT_DATE WHERE EntryID = '" + ui->lstData->getCurrentID() + "'");
			on_dtpDate_dateChanged(ui->dtpDate->date());
		}
	}
}
