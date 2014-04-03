#ifndef SELECTCOMPANYDIALOG_H
#define SELECTCOMPANYDIALOG_H

#include <QDialog>

namespace Ui {
class SelectCompanyDialog;
}

class SelectCompanyDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SelectCompanyDialog(QWidget *parent = 0, QStringList companies = QStringList());
	~SelectCompanyDialog();
	QStringList selectedCompanies();
private slots:
	void on_cmdOK_clicked();

private:
	Ui::SelectCompanyDialog *ui;
	QStringList lst_companies;
};

#endif // SELECTCOMPANYDIALOG_H
