#include "launcherdialog.h"
#include "ui_launcherdialog.h"
#include <QFile>
#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDir>
#include <QApplication>
LauncherDialog::LauncherDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LauncherDialog)
{
	ui->setupUi(this);

	qApp->aboutQt();
	QFile smartSettings("smartpay.ini");
	if (smartSettings.open(QIODevice::ReadWrite)) {
		QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

		QString hostName = "192.168.0.8";
		QString userName = "root";
		QString password = "pledge";
		QString dbName = "smartpay-master";


		QFile file(qApp->applicationDirPath() + QDir::separator() + "smartpay.ini");
		if (file.exists()) {
			if (file.open(QIODevice::ReadOnly)) {
				QString fileData = file.readAll();
				QStringList settings = fileData.split(";");
				for (int i = 0; i < settings.count(); i++) {
					QString thisSetting = settings.at(i);
					if (thisSetting.contains("=")) {
						QStringList settingData = thisSetting.split("=");
						QString setting = settingData.at(0);
						QString value = settingData.at(1);

						if (setting == "h")
							hostName = value;

						if (setting == "u")
							userName = value;

						if (setting == "p")
							password = value;

						if (setting == "d")
							dbName = value;
					}
				}
			}
		} else {
			QString fileData = "h=192.168.0.8;u=root;p=pledge;d=smartpay-megvel";
			if (file.open(QIODevice::WriteOnly)) {
				file.write(fileData.toUtf8());
				file.close();
			}
		}

		db.setHostName(hostName);
		db.setUserName(userName);
		db.setPassword(password);
		db.setDatabaseName(dbName);

		QMessageBox::information(this, "Info", "Going through");
	} else {
		QProcess p(this);
		p.execute("SmartPay.exe");
	}
}

LauncherDialog::~LauncherDialog()
{
	delete ui;
}
