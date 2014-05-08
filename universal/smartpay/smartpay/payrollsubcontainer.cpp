#include "payrollsubcontainer.h"
#include "ui_payrollsubcontainer.h"

#include "alladvances.h"
#include "leavedaysmw.h"
#include "saccosmainwindow.h"
#include "otherdeductionsmw.h"
#include "ta_mw.h"
#include "overtime.h"
#include "overtime_dataentry.h"
#include "dataentry_advances.h"
#include "payroll.h"
#include "payslips.h"
#include "payslips2.h"
#include "../src/payrollreports.h"
PayrollSubContainer::PayrollSubContainer(QWidget *parent, QSqlDatabase database, bool payroll) :
	QMainWindow(parent),
	ui(new Ui::PayrollSubContainer)
{
	ui->setupUi(this);
	canAccessPayroll = payroll;
	db = database;


	m_payroll = new Payroll(this, db);
	m_payslips = new Payslips2(this, db);
	m_advances = new AllAdvances(this, db);
	m_leave_days = new LeaveDaysMW(this, db);
	SaccosMainWindow *sacc = new SaccosMainWindow(this, db);
	OtherDeductionsMW *otherDeds = new OtherDeductionsMW(this, db);
	TaMW *travellingAllowance = new TaMW(this, db);
	//PayrollReports *payr = new PayrollReports(this, db);
	ui->widget->insertTab(m_leave_days);
	ui->widget->insertTab(travellingAllowance);
	ui->widget->insertTab(otherDeds);
	ui->widget->insertTab(m_advances);
	ui->widget->insertTab(sacc);


	if (canAccessPayroll) {
		ui->widget->insertTab(m_payroll);
		ui->widget->insertTab(m_payslips);
		connect (m_payroll, SIGNAL(recalculated()), m_payslips, SLOT(reloadTree()));
		//ui->widget->insertTab(payr);
	}
}

PayrollSubContainer::~PayrollSubContainer()
{
	delete ui;
}
