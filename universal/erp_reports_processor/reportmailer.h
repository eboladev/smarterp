#ifndef REPORTMAILER_H
#define REPORTMAILER_H

#include <QThread>
#include <QtSql>
#include "mailassistant.h"
class ReportMailer : public QThread
{
    Q_OBJECT
public:
    explicit ReportMailer(QObject *parent = 0, QSqlDatabase database = QSqlDatabase(), QString entryID = "-1");
    QSqlDatabase db;
    void run();
signals:
    
private slots:
    void smtpError(QString err);
    void smtpStatus(QString stat);
private:
    QString currentID;
    MailAssistant *as;
};

#endif // REPORTMAILER_H
