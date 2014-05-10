#ifndef DATABASESETUPDIALOG_H
#define DATABASESETUPDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseSetupDialog;
}

class DatabaseSetupDialog : public QDialog
{
	Q_OBJECT

public:
	explicit DatabaseSetupDialog(QWidget *parent = 0);
	~DatabaseSetupDialog();

private slots:
	void on_buttonBox_rejected();

	void on_buttonBox_accepted();

	void on_cmdTestConnection_clicked();

private:
	Ui::DatabaseSetupDialog *ui;
};

#endif // DATABASESETUPDIALOG_H
