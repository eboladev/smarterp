#include "publics.h"
#include <QFile>
#include <QDir>

Publics::Publics(QObject *parent) :
    QObject(parent)
{
}

void Publics::loadDbToComboBox(QSqlDatabase db, QComboBox *cbo, QString query, QString col)
{
    QSqlQuery qy = db.exec(query);
    if (!db.lastError().isValid()) {
        while (qy.next()) {
            cbo->addItem(qy.record().value(col).toString());
        }
    }
}

bool Publics::executeQuery(QSqlDatabase db, QString query, QString error)
{
    QSqlQuery qu = db.exec(query);
    if (qu.lastError().isValid()) {
        error  = qu.lastError().text();
        return false;
    } else {
        return true;
    }
}

QString Publics::getDbValue(QSqlDatabase db, QString query, QString col) {
    QSqlQuery qu = db.exec(query);
    if (!qu.lastError().isValid()) {
        qu.first();
        return  qu.record().value(col).toString();
    }
    return "";
}

#include <QMessageBox>
void Publics::showError(QString error, QString title)
{
    QMessageBox::critical(0, title, error);
}

QSqlDatabase Publics::getDatabase()
{
    QSqlDatabase db = QSqlDatabase::database("debt");
    if (db.isValid()) {
        return db;
    } else {
        return getStartDb();
    }
}

QSqlDatabase Publics::getStartDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "debt");

    QSqlDatabase mainDb = QSqlDatabase::database();

    QString dbName = "debt-collection";

    QString hostName = mainDb.hostName();
    QString userName = mainDb.userName();
    QString password = mainDb.password();

    QFile file(qApp->applicationDirPath() + QDir::separator() + "dcsettings.ini");
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly)) {
            QString fileData = file.readAll();
            QStringList settings = fileData.split(";");
            for (int i = 0; i < settings.count(); i++) {
                QString thisSetting = settings.at(i).trimmed();
                if (thisSetting.contains("=")) {
                    QStringList settingData = thisSetting.split("=");
                    QString setting = settingData.at(0);
                    QString value = settingData.at(1);

                    if (setting == "h")
                        hostName = value;

                    if (setting == "u")
                        userName = value;

                    if (setting == "p")
                        password = value;

                    if (setting == "d")
                        dbName = value;

                    qDebug() << userName << "@" << hostName << "/" << dbName;
                }
            }
        }
    } else {
        QString fileData = "d=debt-collection;";
        if (file.open(QIODevice::WriteOnly)) {
            file.write(fileData.toUtf8());
            file.close();
        }
    }

    db.setHostName(hostName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setDatabaseName(dbName);
    db.open();
    return db;
}

#include "calendar.h"
void Publics::SaveNewAppointment(Appointment *app)
{
    QSqlDatabase db = getDatabase();

    QString customerID = app->customerID();
    QString location = app->place();
    QString subject = app->subject();
    QDateTime startTime = app->startDateTime();
    QDateTime endTime = app->endDateTime();
    QString description = app->description();
    QString isComplete = false;
    if (app->isComplete)
        isComplete = true;

    Calendar *cal = app->calendar();

    if (customerID.length() < 1)
        customerID = "0";

    qDebug() << "New appointment details..." << customerID << location << subject << startTime << endTime << description << cal->key();

    QSqlQuery qu = db.exec("INSERT INTO appointments (AppointmentType, CustomerID, StartDate, StartTime"
                           ", EndDate, EndTime, Location, Subject, "
                           " IsComplete, Description) VALUES ('"
                           + QString::number(cal->key()) + "', '"
                           + customerID + "', '"
                           + startTime.toString("yyyy-MM-dd") + "', '"
                           + startTime.toString("hh:mm:ss")+ "', '"
                           + endTime.toString("yyyy-MM-dd")+ "', '"
                           + endTime.toString("hh:mm:ss")+ "', '"
                           + location + "', '"
                           + subject + "', '"
                           + isComplete  + "', '"
                           + description + "')");
    if (qu.lastError().isValid()) {
        showError(qu.lastError().text());
    }
}
