#include <QCoreApplication>
#include <QDebug>
#include "mailerparent.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "Megvel Cartons Ltd email server";
	MailerParent *mp = new MailerParent(0);
	mp->startParent();
	return a.exec();
}
