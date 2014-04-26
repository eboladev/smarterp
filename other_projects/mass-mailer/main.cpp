#include <QCoreApplication>

#include <QString>
#include "mailassistant.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	for (int i = 0; i < 30; i++) {
		QString sender = "aa" + QString::number(i) + "staff@megvel.me.ke";
		MailAssistant *ma = new MailAssistant(0);
		ma->setVars("Staff no " + sender, "BADOO TEST", QStringList("joejoshw@gmail.com"), QStringList(), sender);

		//ma->start();
	}

	return a.exec();
}
