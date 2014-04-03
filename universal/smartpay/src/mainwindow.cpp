#include "../smartpay/src/mainwindow.h"
#include "ui_mainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"

#include "employees.h"
#include "lists.h"
#include "leaves.h"
#include "payroll.h"
#include "attendance.h"
#include "timetable.h"
#include "admin.h"
#include "payslips.h"
#include "payslips2.h"

#include "userlogin.h"
#include "myaccount.h"
#include "datapublics.h"

#include "attendance2.h"

#include "hr_leaves.h"
#include "payrollsubcontainer.h"

MainWindow::MainWindow(QWidget *parent, QSqlDatabase database, bool demo) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	Utils::StyleHelper::setBaseColor(QColor(128,128,128));
	db = database;
	isDemo = demo;
	//logIn();

	QTimer *tmr = new QTimer(this);
	connect (tmr, SIGNAL(timeout(QPrivateSignal)), SLOT(keepAlive()));
	tmr->start(10000);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::setDatabase(QSqlDatabase database)
{
	db = database;
}

void MainWindow::setCompanyName(QString c)
{
	ui->lblCompanyName->setText(c);
}

void MainWindow::logOff()
{
	/*Not Implemented */
}

void MainWindow::logIn()
{

	QSqlDatabase dbToUse;
	if (isDemo) {
		dbToUse = QSqlDatabase::addDatabase("QMYSQLEMBEDDED", "demo_conn");
		dbToUse.setHostName("localhost");
		dbToUse.setUserName("root");
		dbToUse.setDatabaseName("smartpay_demo");
		if (!dbToUse.open()) {
			QMessageBox::critical(this, "Error", companyDb.lastError().text());
			return;
		}
	} else {
		if (!companyDb.open()) {
			QMessageBox::critical(this, "Error", companyDb.lastError().text());
			return;
		}
		dbToUse = companyDb;
	}




	m_employees = new Employees(this, dbToUse, payrollAccess);
	m_lists = new Lists(this, dbToUse);
	m_lists->payrollAccess = payrollAccess;
	m_lists->resetUI();

	m_acc = new MyAccount(this, dbToUse);

	m_leaves = new HR_Leaves(this, db);

	PayrollSubContainer *m_payrollContainer = new PayrollSubContainer(this, dbToUse, payrollAccess);


	QSqlDatabase attendanceDb = QSqlDatabase::addDatabase("QMYSQL", "attendanceConnection" + dbToUse.databaseName());
	attendanceDb.setHostName(dbToUse.hostName());
	attendanceDb.setUserName(dbToUse.userName());
	attendanceDb.setPassword(dbToUse.password());
	attendanceDb.setDatabaseName(dbToUse.databaseName());
	attendanceDb.open();
	Attendance2 *att = new Attendance2(this, attendanceDb);


	ui->widget->insertTab(m_employees);
	ui->widget->insertTab(att);
	ui->widget->insertTab(m_lists);
	ui->widget->insertTab(m_leaves);
	ui->widget->insertTab(m_payrollContainer);

	ui->widget->setCurrentIndex(0);
}

void MainWindow::keepAlive()
{
	if (db.isOpen())
		db.exec("SELECT NOW()");

	if (companyDb.isOpen())
		companyDb.exec("SELECT NOW()");
}
