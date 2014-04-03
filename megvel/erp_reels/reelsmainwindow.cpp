#include "reelsmainwindow.h"
#include "ui_reelsmainwindow.h"

ReelsMainWindow::ReelsMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ReelsMainWindow)
{
	ui->setupUi(this);
	db = database;
	refresh();
}

ReelsMainWindow::~ReelsMainWindow()
{
	delete ui;
}

void ReelsMainWindow::on_cmdRefresh_clicked()
{
	refresh();
}

void ReelsMainWindow::refresh()
{
	QString query = "SELECT * FROM vw_reels WHERE `Balance` > 0";
	if (ui->chkHideSpentReels->isChecked())
		query = "SELECT * FROM vw_reels";

	ui->lstReels->setQuery(query, db, "Reels", true);
	ui->lstReels->setColumnHidden(0, true);
}

#include "editreel.h"
void ReelsMainWindow::on_cmdEditSelectedReel_clicked()
{
	QString reelID = ui->lstReels->getCurrentID();
	if (reelID.length() > 0) {
		EditReel *ed = new EditReel(this, db, reelID);
		ed->exec();
	}
}
