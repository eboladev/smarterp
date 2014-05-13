#ifndef PAYROLLDBSETTINGSDIALOG_H
#define PAYROLLDBSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class PayrollDbSettingsDialog;
}

class PayrollDbSettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PayrollDbSettingsDialog(QWidget *parent = 0, QString hName = "",
					 QString uName = "",
					 QString pWord = "");
	~PayrollDbSettingsDialog();
	QString hostName, userName, password;
private slots:
	void on_buttonBox_accepted();

private:
	Ui::PayrollDbSettingsDialog *ui;
};

#endif // PAYROLLDBSETTINGSDIALOG_H
