#ifndef LEAVEALLOCATIONEDITOR_H
#define LEAVEALLOCATIONEDITOR_H

#include <QtGui>
#include <QtSql>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
namespace Ui {
class LeaveAllocationEditor;
}

class LeaveAllocationEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit LeaveAllocationEditor(QWidget *parent = 0, QSqlDatabase database =
            QSqlDatabase());
    ~LeaveAllocationEditor();
    QString currentID;
    void Edit(QString id);
    void AddNew(QString employeeID);

private slots:
    void on_cmdSave_clicked();

    void on_calStartDate_dateChanged(const QDate &date);

    void on_calEndDate_dateChanged(const QDate &date);

    void on_chkSat_toggled(bool checked);

    void on_chkSun_toggled(bool checked);

private:
    Ui::LeaveAllocationEditor *ui;
    QSqlDatabase db;
    bool isAdding;
    QString empID;
    int leaveDays;
    void calculateLeaveDays();
};

#endif // LEAVEALLOCATIONEDITOR_H
