#include "freepayrollmw.h"
#include "ui_freepayrollmw.h"
#include "payrollapi.h"


FreePayrollMW::FreePayrollMW(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::FreePayrollMW)
{
	ui->setupUi(this);

	connectionStatusLabel = new QLabel(this);
	companyNameLabel = new QLabel(this);
	currentMonthLabel = new QLabel(this);

	ui->statusBar->addWidget(connectionStatusLabel, 1);
	ui->statusBar->addWidget(companyNameLabel);
	ui->statusBar->addWidget(currentMonthLabel);

	db = QSqlDatabase::addDatabase("QSQLITE", "freepayroll");
	db.setHostName("127.0.0.1");
	db.setDatabaseName("/home/joshua/freepayroll.db");

	if (db.open()) {
		connectionStatusLabel->setText("Connected to database");
		updateCompanyStatusLabelTexts();
	} else {
		PayrollAPI::showError(db.lastError().text());
	}
}

FreePayrollMW::~FreePayrollMW()
{
	delete ui;
}

#include "companyinformationdialog.h"
void FreePayrollMW::on_actionBasic_Info_triggered()
{
	CompanyInformationDialog c(this);
	if (c.exec() == QDialog::Accepted) {
		updateCompanyStatusLabelTexts();
	}
}

void FreePayrollMW::updateCompanyStatusLabelTexts()
{
	QSqlQuery qu = db.exec("SELECT * FROM company");
	qu.first();
	companyNameLabel->setText(qu.record().value("Name").toString());
	currentMonthLabel->setText(qu.record().value("CurrentMonth").toString());
	this->setWindowTitle(companyNameLabel->text());
}

#include "brancheditor.h"
void FreePayrollMW::on_actionBranches_triggered()
{
	BranchEditor *ed = new BranchEditor(this);
	ed->exec();
}

#include "departmenteditor.h"
void FreePayrollMW::on_actionDepartments_triggered()
{
	DepartmentEditor *ed = new DepartmentEditor(this);
	ed->exec();
}

#include "jobgroupeditor.h"
void FreePayrollMW::on_actionJob_Groups_triggered()
{
	JobGroupEditor *ed = new JobGroupEditor(this);
	ed->exec();
}

#include "cooperatives.h"
void FreePayrollMW::on_actionCo_operatives_triggered()
{
	CooperativeEditor *ed = new CooperativeEditor(this);
	ed->exec();
}

#include "pensions.h"
void FreePayrollMW::on_actionPension_Funds_triggered()
{
	PensionEditor *pen = new PensionEditor(this);
	pen->exec();
}

#include "employeeeditor.h"
void FreePayrollMW::on_actionEmployee_triggered()
{
	EmployeeEditor *ed = new EmployeeEditor(this);
	ed->exec();
}

#include "aboutdialog.h"
void FreePayrollMW::on_actionAbout_FreePayroll_triggered()
{
	AboutDialog *ab = new AboutDialog(this);
	ab->exec();
}
