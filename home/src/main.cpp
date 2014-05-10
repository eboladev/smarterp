#include <QApplication>
#include "erpmainwindow.h"

#include <QSqlDatabase>
#include "userlogin.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName("Smart ERP");
	a.setOrganizationName("Panther Technologies");
	a.setApplicationVersion("2.0");
	a.setOrganizationDomain("panthertechno.com");
	UserLogin *log = new UserLogin(0);
	if (log->exec() == QDialog::Accepted) {
		ERPMainWindow *mW = new ERPMainWindow(0, "megvel", "cartons", log->userID, log->db);
		mW->userChanged(log->userName);
		mW->showMaximized();
	} else {
		return 0;
	}

	return a.exec();
}


