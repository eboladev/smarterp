#include "saccomainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SaccoMainWindow w;
	w.show();

	return a.exec();
}
