#include "ims_mw.h"
#include "ui_ims_mw.h"
#include "ims_suppliers.h"
#include "imsmainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "paymentscalendar.h"
#include "ims_reellinker.h"
ims_mw::ims_mw(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ims_mw)
{
	ui->setupUi(this);
	db = database;

	Utils::StyleHelper::setBaseColor(QColor(128,128,128));

	ImsMainWindow *mw = new ImsMainWindow(this, db);
	ui->widget->insertTab(mw);

	PaymentsCalendar *cal = new PaymentsCalendar(this, db);
	ui->widget->insertTab(cal);

	ims_suppliers *s = new ims_suppliers(this, db);
	ui->widget->insertTab(s);

	ims_reellinker *linker = new ims_reellinker(this, db);
	ui->widget->insertTab(linker);

}

ims_mw::~ims_mw()
{
	delete ui;
}
