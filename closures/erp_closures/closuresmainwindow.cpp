#include "closuresmainwindow.h"
#include "ui_closuresmainwindow.h"

#include "fancytabwidget.h"
#include "manhattanstyle.h"
#include "utils/stylehelper.h"
ClosuresMainWindow::ClosuresMainWindow(QWidget *parent, QSqlDatabase database) :
	QMainWindow(parent),
	ui(new Ui::ClosuresMainWindow)
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

	db = database;

	crm_mw = new CRMMainWindow(this);
	prod_mw = new ProductionMW(this);

	ui->widget->insertTab(crm_mw);
	ui->widget->insertTab(prod_mw);
}

ClosuresMainWindow::~ClosuresMainWindow()
{
	delete ui;
}
