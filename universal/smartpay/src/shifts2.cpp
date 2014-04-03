#include "shifts2.h"
#include "ui_shifts2.h"
#include "shifteditor.h"
#include "datapublics.h"
Shifts2::Shifts2(QWidget *parent, QSqlDatabase database) :
	QWidget(parent),
	ui(new Ui::Shifts2)
{
	ui->setupUi(this);
	db = database;
	reloadShifts();
}

Shifts2::~Shifts2()
{
	delete ui;
}

void Shifts2::on_cmdNewShift_clicked()
{
	ShiftEditor *ed = new ShiftEditor(this, db);
	ed->AddNew();
	if (ed->exec() == QDialog::Accepted)
		reloadShifts();
}

void Shifts2::reloadShifts()
{
	ui->lstShifts->setQuery("SELECT * FROM vw_shifts2", db, "Shifts", true);
	ui->lstShifts->setColumnHidden(0, true);
}

void Shifts2::on_lstShifts_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	if (ui->lstShifts->getCurrentID().length() > 0) {
		ShiftEditor *ed = new ShiftEditor(this, db);
		ed->Edit(ui->lstShifts->getCurrentID());
		if (ed->exec() == QDialog::Accepted)
			reloadShifts();
	}
}

void Shifts2::on_cmdDeleteShift_clicked()
{
	if (ui->lstShifts->getCurrentID().length() > 0) {
		if (QMessageBox::question(this, "Confifm Delete", "Are you sure you want to delete this shift?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
			db.exec("DELETE FROM shifts WHERE ShiftID = '" + ui->lstShifts->getCurrentID() + "'");
			reloadShifts();
		}
	} else {
		DataPublics::showWarning("No shift selected for deletion.");
	}
}
