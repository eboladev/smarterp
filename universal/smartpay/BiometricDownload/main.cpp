#include "bdmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setApplicationDisplayName("Biometric Download");
	a.setOrganizationDomain("freesoftware.co.ke");
	a.setOrganizationName("Free Software Kenya");
	a.setApplicationName("BiometricDownload");


	BDMainWindow w;
	w.show();

	return a.exec();
}
