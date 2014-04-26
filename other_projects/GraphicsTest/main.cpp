#include "gtestmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GTestMainWindow w;
	w.show();

	return a.exec();
}
