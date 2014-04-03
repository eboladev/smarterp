#include "tawizard.h"
#include "ui_tawizard.h"
#include "datapublics.h"

TAWizard::TAWizard(QWidget *parent, QSqlDatabase database) :
	QWizard(parent),
	ui(new Ui::TAWizard)
{
	ui->setupUi(this);
	db = database;
	DataPublics::loadQueryToComboBox("SELECT * FROM vw_months_ex ORDER BY MonthID DESC", "Month", db, ui->cboMonths);
	QSqlQuery qu = db.exec("SELECT * FROM vw_employeenames_all ORDER BY `#` ASC");
	while (qu.next()) {
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->lstEmployees);
		it->setText(0, qu.record().value("#").toString());
		it->setText(1, qu.record().value("Name").toString());
		it->setText(99, qu.record().value("EmployeeID").toString());
		it->setCheckState(0, Qt::Unchecked);
	}
	//ui->dtpAdvanceDate->setDate(QDate::currentDate());
	ui->tblTA->setColumnHidden(3, true);
}

TAWizard::~TAWizard()
{
	delete ui;
}


void TAWizard::on_commandLinkButton_clicked()
{
	QString monthID = DataPublics::getDbValue("SELECT * FROM vw_months_ex WHERE Month = '" + ui->cboMonths->currentText() + "'", db, "MonthID").toString();
	QString quError = "";
	for (int i = 0; i < ui->tblTA->rowCount(); i++) {
		QString employeeID = ui->tblTA->item(i, 3)->text();
		QString advance = ui->tblTA->item(i, 2)->text();

		QSqlQuery qu =  db.exec("INSERT INTO ta (EmployeeID, MonthID, Amount) VALUES ('"
					+ employeeID + "', '"
					+ monthID + "', '"
					+ advance + "')");
		if (qu.lastError().isValid()) {
			quError.append(qu.lastError().text());
		} else {
			this->accept();
		}
	}

	if (quError.length() > 0) {
		DataPublics::showWarning("An error has occured.\nData not saved");
		//qDebug() << quError;
	}
}


void TAWizard::on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	QString employeeID = item->text(99);
	QString employeeName = item->text(1);
	QString rollNo = item->text(0);
	bool exists = false;
	for (int i = 0; i < ui->tblTA->rowCount(); i++) {
		if (ui->tblTA->item(i, 3)->text() == employeeID) {
			exists = true;
			if (item->checkState(0) == Qt::Checked) {
				ui->tblTA->removeRow(i);
				return;
			} else {
				return;
			}
		}
	}
	//Not found
	if (!exists && item->checkState(0) == Qt::Checked) {
		QTableWidgetItem *rollNoItem = new QTableWidgetItem(1);
		QTableWidgetItem *nameItem = new QTableWidgetItem(1);
		QTableWidgetItem *AdvanceItem = new QTableWidgetItem(1);
		QTableWidgetItem *idItem = new QTableWidgetItem(1);

		rollNoItem->setText(rollNo);
		nameItem->setText(employeeName);
		AdvanceItem->setText("0");
		idItem->setText(employeeID);

		int r = ui->tblTA->rowCount();
		ui->tblTA->insertRow(r);

		ui->tblTA->setItem(r, 0, rollNoItem);
		ui->tblTA->setItem(r, 1, nameItem);
		ui->tblTA->setItem(r, 2, AdvanceItem);
		ui->tblTA->setItem(r, 3, idItem);
	}

	ui->tblTA->setColumnHidden(3, true);
}

void TAWizard::on_cboMonths_currentIndexChanged(const QString &arg1)
{
	Q_UNUSED(arg1);
}
