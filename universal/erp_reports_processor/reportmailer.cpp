#include "reportmailer.h"
#include "mailassistant.h"
#include <QTextDocument>
#include <QPrinter>
ReportMailer::ReportMailer(QObject *parent, QSqlDatabase database, QString entryID) :
    QThread(parent)
{

    as = new MailAssistant(this);
    db = database;
    currentID = entryID;
    connect (as, SIGNAL(errorOccurred(QString)), SLOT(smtpError(QString)));
    connect (as, SIGNAL(messageStatus(QString)), SLOT(smtpStatus(QString)));
}

void ReportMailer::run()
{
    //as->moveToThread(this);
    qDebug() << "===NEW SMTP THREAD STARTED===";

    QSqlQuery qu = db.exec("SELECT * FROM scheduled_reports_queue WHERE EntryID = '" + currentID + "'");
    if (qu.lastError().isValid()) {
        qDebug() << "SMTP/SQL ERROR: " << qu.lastError().text();
    }  else {
        while (qu.next()) {
            //Move timestamp up
            db.exec("UPDATE scheduled_reports_queue SET LastAttempt = NOW(),  NextAttempt = DATE_ADD(NOW(), INTERVAL 2 MINUTE) WHERE EntryID = '" + currentID + "'");
            QString subject = qu.record().value("Subject").toString();
            QStringList recepients;
            QString s_rec = qu.record().value("Recepients").toString();
            recepients = s_rec.split(";");
            recepients.removeLast();
            qDebug() << recepients;
            QStringList attachments;
            QString msg = qu.record().value("ReportHTML").toString();

            //Generate PDF attachment
            QString queueID = currentID; //insQu.lastInsertId().toString();
            //Generate PDF and save it to db.
            QTextDocument textEdit;
            textEdit.setHtml(msg);
            QString fileName = QDir::tempPath() + QDir::separator() + subject + "_" + queueID + ".pdf";
            if (!fileName.isEmpty()) {
                if (QFileInfo(fileName).suffix().isEmpty())
                    fileName.append(".pdf");
                QPrinter printer(QPrinter::HighResolution);
                printer.setOrientation(QPrinter::Landscape);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);
                textEdit.print(&printer);
                attachments.append(fileName);
            }


            as->setVars(subject, msg, recepients, attachments, "\"Megvel Cartons Ltd ERP\" <smart-erp@pmegvel.me.ke>");
            as->start();
        }
    }
}

void ReportMailer::smtpError(QString err)
{
    qDebug() << "===SMTP ERROR " << err;
    db.exec("UPDATE scheduled_reports_queue SET LastError = '" + err + "' WHERE EntryID = '" + currentID  + "'");
}

void ReportMailer::smtpStatus(QString stat)
{
    db.exec("UPDATE scheduled_reports_queue SET LastStatus = '" + stat + "' WHERE EntryID = '" + currentID  + "'");
    qDebug() << "===SMTP Status: " << stat;
    if (stat == "Message successfully sent") {
        db.exec("UPDATE scheduled_reports_queue SET EmailSent  = '1' WHERE EntryID = '" + currentID  + "'");
    }
}
