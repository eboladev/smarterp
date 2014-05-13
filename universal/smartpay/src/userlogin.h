#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QtSql>

#include <QDialog>
#include <QSettings>
namespace Ui {
class UserLogin;
}

class UserLogin : public QDialog
{
	Q_OBJECT

public:
	explicit UserLogin(QWidget *parent = 0);
	~UserLogin();
	bool payrollAccess;
	QString userID;
	QSqlDatabase companyDb;
	QString companyName;
	QStringList companies;
	QSqlDatabase db;
private:
	Ui::UserLogin *ui;
	QString hostName, userName, password;
private slots:
	void tryLogin();
	void on_cmdAuthConfig_clicked();

	void setSettingValue(QString settingName, QVariant value);
	QVariant getSettingValue(QString settingName, QVariant defaultValue);
};

#endif // USERLOGIN_H
