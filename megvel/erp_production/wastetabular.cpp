#include "wastetabular.h"
#include "ui_wastetabular.h"

WasteTabular::WasteTabular(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::WasteTabular)
{
	ui->setupUi(this);
	ui->dtpStart->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
	ui->dtpEnd->setDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().daysInMonth()));

	reloadList();
}

WasteTabular::~WasteTabular()
{
	delete ui;
}

void WasteTabular::reloadList()
{
	QSqlDatabase db = QSqlDatabase::database();
	ui->trvWaste->setQuery("SELECT * FROM vw_paras_waste WHERE Date BETWEEN '" + ui->dtpStart->date().toString("yyyy-MM-dd") + "' AND '" + ui->dtpEnd->date().toString("yyyy-MM-dd") + "'", db, "Paper Waste Report", true);
	ui->trvWaste->setColumnHidden(0, true);
}

#include "newwasteentry.h"
void WasteTabular::on_action_New_Entry_triggered()
{
	NewWasteEntry *w = new NewWasteEntry(this);
	if (w->exec() == QDialog::Accepted)
		reloadList();
}
