#include "mailerparent.h"
#include "QDebug"
MailerParent::MailerParent(QObject *parent) :
	QObject(parent)
{

}

void MailerParent::startParent()
{
	count = 0;
	QTimer *tmr = new QTimer(this);
	connect (tmr, SIGNAL(timeout()), SLOT(onTimer()));
	tmr->start(1000);
}

void MailerParent::onTimer()
{
	count ++;
	qDebug() << "Interval " << count;
}
