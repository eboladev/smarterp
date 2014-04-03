#ifndef PUBLICS_H
#define PUBLICS_H

#include <QObject>
#include <QtSql>
#include "appointment.h"
#include  <QDebug>

class Publics : public QObject
{
    Q_OBJECT
public:
    explicit Publics(QObject *parent = 0);
    static void loadDbToComboBox(QSqlDatabase db, QComboBox *cbo, QString query, QString col);
    static bool executeQuery(QSqlDatabase db, QString query, QString error = QString());
    static QString getDbValue(QSqlDatabase db, QString query, QString col);
    static void  showError(QString error, QString title="Error");
    static QSqlDatabase getDatabase();
    static QSqlDatabase getStartDb();

    static void SaveNewAppointment(Appointment *app);
signals:

    
public slots:
    
};

#endif // PUBLICS_H
