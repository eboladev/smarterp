#ifndef ATTENDANCE2_H
#define ATTENDANCE2_H

#include <QMainWindow>
#include <QtSql>
#include <QTimer>
namespace Ui {
class Attendance2;
}

class BiometricProcessor : public QObject {
    Q_OBJECT
public:
    explicit BiometricProcessor(QObject *parent);
    void setVars(QSqlDatabase database);
    void setEntries(QStringList entries);
signals:
    void progress(int);
    void total(int);
    void progress_data(QString);
    void finished();
    void error(QString err);
private:
    QStringList lst_entries;
    QSqlDatabase db;
public slots:
    void processAllUnprocessed();
    void processEntries();
};

class Attendance2 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Attendance2(QWidget *parent = 0, QSqlDatabase d = QSqlDatabase());
    ~Attendance2();

private slots:
    void reloadProcessedandMain();
    void reloadAttendance(bool mainAttendance = true,
                          bool rawAttendance = true,
                          bool processedAttendance = true
                          );

    void on_actionNew_Attendance_Entry_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_cmdDelete_clicked();

    void on_actionLeaves_Absent_triggered();

    void on_lstAttendance_doubleClicked(const QModelIndex &index);

    void on_cmdChangeShift_clicked();

    void on_cmdChangeDate_clicked();

    void on_actionRefresh_triggered();

    void on_actionRecalculate_triggered();

    void on_cboMonths_currentIndexChanged(const QString &arg1);

    void generateEmployeeMonthlyAttendanceReport();

    void on_cmdReloadRPT1_clicked();

    void on_actionImport_Biometric_Data_triggered();

    void on_actionAssign_Shifts_triggered();

    void on_cmdProcessUnprocessed_clicked();

    void processorFinished();
    void biometricProgress(int val);
    void biometricTotal(int val);
    void biometricProgressData(QString data);
    void biometricError(QString error);
    void on_actionImport_Biometric_Attendance_triggered();

    void on_actionRecalculate_All_Entries_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_cmdChangeRawEntry_clicked();

    void on_cmdDeleteRawData_clicked();

    void on_cmdDeleteProcessedData_clicked();

    void on_dbTimer();
    void on_cmdAssignBiometricShift_clicked();

    void on_dtpProcessed_dateChanged(const QDate &date);

    void on_cboAttendanceEmployee_currentIndexChanged(const QString &arg1);

    void on_chkAttendanceAllEmployees_toggled(bool checked);

private:
    Ui::Attendance2 *ui;
    QSqlDatabase db;
    bool isClosed;
    QTimer *timer;
    QTimer *dbTimer;
};

#endif // ATTENDANCE2_H
