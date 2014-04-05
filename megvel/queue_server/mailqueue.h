#ifndef MAILQUEUE_H
#define MAILQUEUE_H

#include <QThread>
#include <QtSql>
#include <QTimer>
class MailQueue : public QThread
{
	Q_OBJECT
public:
	explicit MailQueue(QObject *parent = 0);
	void run();
signals:
	void message(QString msg);

public slots:

private:
	QSqlDatabase db;
	QTimer *mailTimer;
	bool started;
private slots:
	void onMailTimer();

	void smtpError(QString err);
	void smtpSuccess(QString msg);
};

#endif // MAILQUEUE_H
