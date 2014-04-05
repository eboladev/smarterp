#include "qsmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QSMainWindow w;
	w.show();

	return a.exec();
}
