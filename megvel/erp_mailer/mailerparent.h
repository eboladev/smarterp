#ifndef MAILERPARENT_H
#define MAILERPARENT_H

#include <QObject>
#include <QtSql>
#include <QThread>
#include <QStringList>
#include "smtpclient/emailaddress.h"
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
	void openDatabase();
	QDateTime startTime;
	QString table_name;
	bool sendOc(QString ocNo);
	bool sendRequisition(QString rqnNo);
	bool sendEmail(QString subject, QString messageText,
		       QStringList recepients, QStringList attachments = QStringList());
	EmailAddress *getEmailFromString(QString email);
};

#endif // MAILERPARENT_H
