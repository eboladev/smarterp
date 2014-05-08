#include "samainwindow.h"
#include "ui_samainwindow.h"
#include "datapublics.h"
#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif

#include "memberdetails.h"

SaMainWindow::SaMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SaMainWindow)
{
	ui->setupUi(this);

	QString baseName = QApplication::style()->objectName();
	#ifdef Q_WS_X11
		if (baseName == QLatin1String("windows")) {
			// Sometimes we get the standard windows 95 style as a fallback
			// e.g. if we are running on a KDE4 desktop
			QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
			if (desktopEnvironment == "kde")
				baseName = QLatin1String("plastique");
			else
				baseName = QLatin1String("cleanlooks");
		}
	#endif
		qApp->setStyle(new ManhattanStyle(baseName));

		Utils::StyleHelper::setBaseColor(QColor(128,128,128));

	QString connectionName = "sacco";
	QString hostName = "127.0.0.1";
	QString userName = "root";
	//QString password = "pledge";
	int port = 3306;
	QString dbName = "macopri";

	db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
	db.setHostName(hostName);
	db.setUserName(userName);
	//db.setPassword(password);
	db.setPort(port);
	db.setDatabaseName(dbName);

	if (db.open()) {
		ui->statusBar->showMessage("Connected to server.");
	} else {
		ui->statusBar->showMessage("Server connection failed: " + db.lastError().text());
		DataPublics::showWarning("<B>Database Error</b><br/>" + db.lastError().text());
	}

	MemberDetails *mem = new MemberDetails(this);
	ui->widget->insertTab(mem);
}

SaMainWindow::~SaMainWindow()
{
	delete ui;
}
