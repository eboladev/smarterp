#include "queueprocessor.h"
#include "reportmailer.h"

QueueProcessor::QueueProcessor(QObject *parent, QSqlDatabase database) :
    QThread(parent)
{
    running  =false;
    tmr = new QTimer();
    db = database;
    connect (tmr, SIGNAL(timeout()), SLOT(timeOut()));
    tmr->start(10000);
}

void QueueProcessor::run()
{
    qDebug() << "Queue Processor Started";
    tmr->moveToThread(this);
    running = true;
}

void QueueProcessor::timeOut()
{
    if (running) {
        qDebug() << "Queue Timeout";
        QSqlQuery qu = db.exec("SELECT * FROM scheduled_reports_queue WHERE EmailSent = '0' AND NextAttempt <= NOW()");
        while (qu.next()) {
            QSqlRecord rec = qu.record();
            QString entryID = rec.value("EntryID").toString();
            qDebug() << "Starting 1 mailer";
            ReportMailer *ma =  new ReportMailer(this, db, entryID);
            ma->start();
        }
    }
}
