#ifndef MAILERPARENT_H
#define MAILERPARENT_H

#include <QObject>
#include <QtSql>

class MailerParent : public QObject
{
	Q_OBJECT
public:
	explicit MailerParent(QObject *parent = 0);
	void startParent();
signals:

public slots:
	void onTimer();
private:
	QSqlDatabase db;
	int count;


};

#endif // MAILERPARENT_H
