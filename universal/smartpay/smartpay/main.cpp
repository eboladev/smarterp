
#include <QApplication>
#include <QtSql>
#include "mainwindow.h"
#include "datapublics.h"

#include "payrollcontainer.h"
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "payrollConnection");

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
				QString thisSetting = settings.at(i).trimmed();
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

					//qDebug() << userName << "@" << hostName << "/" << dbName;
				}
			}
		}
	} else {
		QString fileData = "h=192.168.0.8;u=root;p=pledge;d=smartpay-master";
		if (file.open(QIODevice::WriteOnly)) {
			file.write(fileData.toUtf8());
			file.close();
		}
	}

	db.setHostName(hostName);
	db.setUserName(userName);
	db.setPassword(password);
	db.setDatabaseName(dbName);
	if (db.open()) {
		PayrollContainer w(0, db, false);
		w.showMaximized();
		return a.exec();
	} else {
		QMessageBox::critical(0, "Database Error", "<h3>Could not connect to database.</h3> <br/>" + db.lastError().text());
		return 0;
	}

}
