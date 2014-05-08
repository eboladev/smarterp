#include "samainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setApplicationDisplayName("Smart Sacco Management System");
	a.setApplicationName("ssms");
	a.setOrganizationDomain("freesoftware.co.ke");
	a.setOrganizationName("Free Software (k) ltd");
	a.setApplicationVersion("1.0.0");

	SaMainWindow w;
	w.showMaximized();


	return a.exec();
}
