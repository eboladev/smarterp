#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("DB Studios");
	a.setApplicationName("SQLite Management Studio");
	a.setApplicationVersion("2.0.0");
	MainWindow w;
	w.show();
	return a.exec();
}
