#include "freepayrollmw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setApplicationDisplayName("Free Payroll 1.3");
	a.setApplicationName("freepayrollke");
	a.setApplicationVersion("1.3");
	a.setOrganizationName("Smart Software (k) Ltd");

	FreePayrollMW w;
	w.showMaximized();
	a.setStyle("Fusion");
	return a.exec();
}
