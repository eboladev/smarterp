#include "intromainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IntroMainWindow w;
	w.show();

	return a.exec();
}
