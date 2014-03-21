#ifndef MAILASSISTANT_H
#define MAILASSISTANT_H

#include <QObject>
#include <QThread>
#include <QStringList>
class MailAssistant : public QThread
{
    Q_OBJECT
public:
    explicit MailAssistant(QObject *parent = 0);
    QString fromEmail;
    QString fromName;
    QString subject;
    QStringList attachments;
    QStringList recepients;
    QString messageBody;
    QString errorMessage;

    void run();

    void setVars(QString Subject, QString Message, QStringList Recepients = QStringList(), QStringList Attachments = QStringList(),
                 QString From = "smart-erp@megvel.me.ke");

signals:
    void errorOccurred(QString);
    void messageStatus(QString);
public slots:
    
};

#endif // MAILASSISTANT_H
