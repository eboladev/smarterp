
#include <QApplication>

#include "payrollcontainer.h"
#include "userlogin.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	UserLogin login(0);

	if (login.exec() == QDialog::Accepted) {
		PayrollContainer w(0, false, login.companies, login.userID);
		w.showMaximized();
		return a.exec();
	} else {
		qApp->quit();
	}
}
