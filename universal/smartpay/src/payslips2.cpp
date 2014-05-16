#include "payslips2.h"
#include "ui_payslips2.h"
#include "./qtprinter.h"
#include "quickprinter.h"
Payslips2::Payslips2(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::Payslips2)
{
	ui->setupUi(this);
	db = database;

	reloadTree();
}

Payslips2::~Payslips2()
{
	delete ui;
}

void Payslips2::on_cmdGenerate_clicked()
{
	QString paramWhere = " WHERE ";
	for (int i = 0; i < ui->lstEmployees->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *monthItem = ui->lstEmployees->invisibleRootItem()->child(i);
		for (int e = 0; e < monthItem->childCount(); e++) {
			QTreeWidgetItem *it = monthItem->child(e);
			if (it->checkState(0) == Qt::Checked) {
				paramWhere += " EntryID = '" + it->text(99) + "' OR";
			}
		}
	}
	paramWhere = paramWhere.left(paramWhere.length() - 3);
	////qDebug() << paramWhere;

	//QtPrinter *qp = new QtPrinter(this, db, paramWhere, "Payslips4x1", ui->chkPdf->isChecked());
	QuickPrinter(this, "Payslips4x1", paramWhere, db, ui->chkPdf->isChecked());

	//Q_UNUSED(qp);
}

void Payslips2::reloadTree()
{
	ui->lstEmployees->invisibleRootItem()->takeChildren();
	QSqlQuery monthsQuery = db.exec("SELECT * FROM vw_months_ex ORDER BY MonthID DESC");
	while (monthsQuery.next()) {
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstEmployees);
		it->setText(0, monthsQuery.record().value("Month").toString());
		it->setText(100, "Month");
		it->setText(99, monthsQuery.record().value("MonthID").toString());

		QString monthID = monthsQuery.record().value("MonthID").toString();
		QString monthName = monthsQuery.record().value("Month").toString();

		it->setCheckState(0, Qt::Unchecked);
		QSqlQuery qu = db.exec("SELECT * FROM payroll WHERE MonthID = '" + monthID + "'");
		while (qu.next()) {
			QTreeWidgetItem *empIt = new QTreeWidgetItem(it);
			empIt->setText(99, qu.record().value("EntryID").toString());
			empIt->setText(100, "Emp");
			empIt->setIcon(0, QIcon(":/payroll/images/Users.png"));
			empIt->setText(0, qu.record().value("EmployeeNo").toString() + "-" + qu.record().value("EmployeeName").toString());
			empIt->setText(1, monthName);
			empIt->setCheckState(0, Qt::Unchecked);
		}
	}
}

void Payslips2::on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	if (item->text(100) == "Month") {
		for (int i = 0; i < item->childCount(); i++) {
			item->child(i)->setCheckState(0, item->checkState(0));
		}
	}
}
