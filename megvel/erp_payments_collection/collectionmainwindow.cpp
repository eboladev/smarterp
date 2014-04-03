#include "collectionmainwindow.h"
#include "ui_collectionmainwindow.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#include "datapublics.h"

#include "col_customerlist.h"
#include "col_invoicelist.h"
#include "col_localinvoices.h"
#include "col_ageing.h"
CollectionMainWindow::CollectionMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::CollectionMainWindow)
{
	ui->setupUi(this);
	Utils::StyleHelper::setBaseColor(QColor(128,128,128));
	db = database;

	//col_CustomerList *custs = new col_CustomerList(this);
	//col_InvoiceList *inv  = new col_InvoiceList(this);
	col_LocalInvoices *loc = new col_LocalInvoices(this, db);
	Col_Ageing *ag = new Col_Ageing(this, db);

	//ui->widget->insertTab(custs);
	//ui->widget->insertTab(inv);
	ui->widget->insertTab(ag);
	ui->widget->insertTab(loc);

}

CollectionMainWindow::~CollectionMainWindow()
{
	delete ui;
}
