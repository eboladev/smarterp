#include "scheduleprocessor.h"
#include "htmlgenerator.h"

#include "reportmailer.h"
#include <QTextDocument>
#include <QTextBrowser>
#include <QPrinter>

ScheduleProcessor::ScheduleProcessor(QObject *parent, QSqlDatabase database) :
    QObject(parent)
{
    db = database;
    qDebug () << "Smart ERP Report Scheduler (1.0)";
    tmrSec = new QTimer(this);
    connect (tmrSec, SIGNAL(timeout()), SLOT(timeOut()));
    tmrSec->start(60000);
    timeOut();

    tmrMailer = new QTimer(this);
    connect (tmrMailer, SIGNAL(timeout()), SLOT(mailer()));
    tmrMailer->start(1000);
}

void ScheduleProcessor::timeOut()
{
    qDebug() << "=================================";
    qDebug() << "";
    qDebug() << "Checking for reports scheduled for: " + QDateTime::currentDateTime().toString("hh:mm dd-MMM-yyyy");


    QString month = QDate::currentDate().toString("MM");
    QString day = QDate::currentDate().toString("dd");
    QString hour = QTime::currentTime().toString("hh");
    QString minute = QTime::currentTime().toString("mm");

    QSqlQuery qu = db.exec("SELECT * FROM scheduled_reports_schedule "
                           "WHERE "
                           "( "
                           "((`Months` LIKE '%All%') OR (`Months` LIKE '%" + month + "%')) "
                           "AND "
                           "((`Days` LIKE '%All%') OR (`Days` LIKE '%" + day + "%')) "
                           "AND "
                           "((`Hours` LIKE '%All%') OR (`Hours` LIKE '%" + hour + "%')) "
                           "AND "
                           "((`Minutes` LIKE '%All%') OR (`Minutes` LIKE '%" + minute + "%')) "
                           ")");
    if (qu.lastError().isValid()) {
        qDebug() << "Database error: " << qu.lastError().text() << ".\nOpening db connection again.";
        db.open();
    } else {
        int foundReports = qu.size();
        qDebug() << "Found " + QString::number(foundReports) + " reports matching current timestamp. Processing them now.";
        while (qu.next()) {
            qDebug() << "=================================";
            qDebug() << "";

            QSqlQuery qu2 = db.exec("SELECT * FROM scheduled_reports WHERE ReportID = '" + qu.record().value("ReportID").toString() + "'");
            qu2.first();
            qDebug() << "Report: " << qu2.record().value("ReportName").toString();
            qDebug() << "SQL: " << qu2.record().value("ReportSQL").toString();


            QString html  = HtmlGenerator::showReportHtml(qu.record().value("ReportID").toString(), db);

            QSqlQuery recQu = db.exec("SELECT "
                                      "    scheduled_reports_recepients.ReportID "
                                      "    , users.FullName "
                                      "    , users.Email "
                                      "FROM "
                                      "    cartons.scheduled_reports_recepients "
                                      "    INNER JOIN cartons.users  "
                                      "        ON (scheduled_reports_recepients.UserID = users.UserID) WHERE ReportID = '" + qu.record().value("ReportID").toString() + "'");

            QString recepients = "";
            if (recQu.lastError().isValid()) {
                qDebug() << "Recepient Error: " << recQu.lastError().text();
            } else {
                while (recQu.next()) {
                    QString name = recQu.record().value("FullName").toString();
                    QString email = recQu.record().value("Email").toString();
                    if (email.length() > 0) {
                        recepients += "\"" + name + "\" <" + email + ">;";
                        //recepients += email;
                    }
                }
            }

            qDebug() << "Recepients: " << recepients;


            QString title = qu2.record().value("ReportTitle").toString();
            title.replace("{UserDate}", QDate::currentDate().toString("dd-MMM-yyyy"));

            QSqlQuery insQu = db.exec("INSERT INTO scheduled_reports_queue (ReportID, Date, Time, ReportHTML, Recepients, Subject, NextAttempt)"
                                      "VALUES ('"
                                      + qu.record().value("ReportID").toString() + "', "
                                      + "CURRENT_DATE(), CURRENT_TIME(), '"
                                      + html  + "', '"
                                      + recepients  + "', '"
                                      + title   + "', "
                                      + "NOW())");
            if (db.lastError().isValid()) {
                qDebug() << "Error while saving queue: " << db.lastError().text();
            } else {
                qDebug() << "Report added to queue. Will be sent soon";
            }

            qDebug() << "=================================";
            qDebug() << "";
        }
    }


    qDebug() << "=================================";
    qDebug() << "";
    qDebug() << "";
}

void ScheduleProcessor::mailer()
{
    QSqlQuery qu =   db.exec("SELECT * FROM scheduled_reports_queue WHERE EmailSent = '0' AND NextAttempt <= NOW()");
    if (qu.size()) {
        qu.first();
        ReportMailer *rpt = new ReportMailer(this, db, qu.record().value("EntryID").toString());
        rpt->start();

    }
    //}
}
