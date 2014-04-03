#include "company.h"
#include "ui_company.h"
#include "users.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include <QMessageBox>
#include "rolesmanager.h"
#include "salesreps.h"
#include "datamanager.h"

Company::Company(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Company)
{
	ui->setupUi(this);

	ui->mainToolBar->setStyleSheet("QToolButton { border-image: url(:/images/panel_button.png) 2 2 2 19;"
				       " border-width: 2px 2px 2px 19px; padding-left: -17; padding-right: 4 } "
				       "QToolButton:checked { border-image: url(:/images/panel_button_checked.png) 2 2 2 19 } "
				       "QToolButton::menu-indicator { width:0; height:0 }"
			       #ifndef Q_WS_MAC // Mac UIs usually don't hover
				       "QToolButton:checked:hover { border-image: url(:/images/panel_button_checked_hover.png) 2 2 2 19 } "
				       "QToolButton:pressed:hover { border-image: url(:/images/panel_button_pressed.png) 2 2 2 19 } "
				       "QToolButton:hover { border-image: url(:/images/panel_button_hover.png) 2 2 2 19 } "
			       #endif
				       );
	db = database;
	Utils::StyleHelper::setBaseColor(QColor(128,128,128));

	t_users = new Users(this, db);
	ui->widget->insertTab(t_users);

	t_reps = new SalesReps(this, db);
	ui->widget->insertTab(t_reps);

	t_dataman = new DataManager(this, db);
	ui->widget->insertTab(t_dataman);
}

Company::~Company()
{
	delete ui;
}


void Company::reload()
{

}

void Company::on_actionView_Edit_User_Roles_triggered()
{
	RolesManager *rm = new RolesManager(this, db);
	if (rm->exec()) {

	}
}
