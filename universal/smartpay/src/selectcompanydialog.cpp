#include "selectcompanydialog.h"
#include "ui_selectcompanydialog.h"

SelectCompanyDialog::SelectCompanyDialog(QWidget *parent, QStringList companies) :
	QDialog(parent),
	ui(new Ui::SelectCompanyDialog), lst_companies(companies)
{
	ui->setupUi(this);
	for (int i = 0; i < companies.count(); i++) {
		QTreeWidgetItem *it = new QTreeWidgetItem(ui->treeWidget->invisibleRootItem());
		it->setText(0, companies.at(i));
		it->setCheckState(0, Qt::Checked);
	}
}

SelectCompanyDialog::~SelectCompanyDialog()
{
	delete ui;
}

QStringList SelectCompanyDialog::selectedCompanies()
{
	QStringList ret;
	for (int i = 0; i < ui->treeWidget->invisibleRootItem()->childCount(); i++) {
		QTreeWidgetItem *it = ui->treeWidget->invisibleRootItem()->child(i);
		if (it->checkState(0) == Qt::Checked)
			ret.append(it->text(0));
	}

	return ret;
}

void SelectCompanyDialog::on_cmdOK_clicked()
{
	this->accept();
}
