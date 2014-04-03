#include "users.h"
#include "ui_users.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>

Users::Users(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Users)
{
	ui->setupUi(this);
	db = database;
	usersModel = new QSqlQueryModel(this);
	reloadUsers();
}

Users::~Users()
{
	delete ui;
}

void Users::on_cmdAddNew_clicked()
{
	UserEditor *ed = new UserEditor(this, db);
	ed->addNew();
	if (ed->exec()) {
		reloadUsers();
	}
}

void Users::reloadUsers()
{
	usersModel->setQuery("SELECT * FROM vw_users", db);

	ui->lstUSers->setQuery("SELECT * FROM vw_users", db, "Users", true);
	ui->lstUSers->setColumnHidden(0, true);
}


void Users::on_lstUSers_doubleClicked(const QModelIndex &index)
{
	Q_UNUSED(index);
	//QString currentID = ui->lstUSers->myModel->record(index.row()).value(0).toString();
	QString currentID = ui->lstUSers->getCurrentID();
	UserEditor *ed = new UserEditor(this, db);
	ed->currentID = currentID;
	ed->edit();
	if (ed->exec()) {
		reloadUsers();
	}
}
