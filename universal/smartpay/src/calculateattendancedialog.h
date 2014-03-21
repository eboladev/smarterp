#ifndef CALCULATEATTENDANCEDIALOG_H
#define CALCULATEATTENDANCEDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CalculateAttendanceDialog;
}


class AttendanceCalculator : public QObject {
    Q_OBJECT
public:
    explicit AttendanceCalculator(QObject *parent);
    void setVars(QSqlDatabase database, QStringList lst);
signals:
    void progress(int);
    void progressData(QString);
    void finished();
private:
    QStringList entries;
    QSqlDatabase db;
    bool stop;
public slots:
    void startProcessing();
    void cancelAll();
};

class CalculateAttendanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculateAttendanceDialog(QWidget *parent = 0,
                                       QStringList entriesToCalculate = QStringList()
                                       , QSqlDatabase =
            QSqlDatabase()
                                       );
    ~CalculateAttendanceDialog();
    QStringList m_entries;
    QStringList entries() const;
    void setEntries(const QStringList &entries);

    QSqlDatabase db() const;
    void setDb(const QSqlDatabase &db);
signals:
    void allDone();
public slots:
    void on_cmdRecalculate_clicked();

private:
    Ui::CalculateAttendanceDialog *ui;
    QSqlDatabase m_db;
};

#endif // CALCULATEATTENDANCEDIALOG_H
