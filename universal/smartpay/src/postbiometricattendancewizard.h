#ifndef POSTBIOMETRICATTENDANCEWIZARD_H
#define POSTBIOMETRICATTENDANCEWIZARD_H

#include <QWizard>
#include <QtSql>
namespace Ui {
class PostBiometricAttendanceWizard;
}

class PostBiometricAttendanceWizard : public QWizard
{
    Q_OBJECT

public:
    explicit PostBiometricAttendanceWizard(QWidget *parent = 0
            , QSqlDatabase d = QSqlDatabase());
    ~PostBiometricAttendanceWizard();
private slots:
    void reloadEmployees();
    void on_dtpDate_dateChanged(const QDate &date);
    void pageChanged(int pageNum);
    void on_cmdSave_clicked();

private:
    Ui::PostBiometricAttendanceWizard *ui;
    QSqlDatabase db;
    bool saved;
};

#endif // POSTBIOMETRICATTENDANCEWIZARD_H
