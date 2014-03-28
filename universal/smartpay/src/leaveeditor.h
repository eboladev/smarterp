#ifndef LEAVEEDITOR_H
#define LEAVEEDITOR_H

#include <QtGui>
#include <QtSql>
#include <QDialog>

namespace Ui {
class LeaveEditor;
}

class LeaveEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit LeaveEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~LeaveEditor();
    void AddNew(QString AllocationNo);
    void Edit(QString LeaveNo);
private slots:
    void on_optMultiple_clicked();

    void on_optSingle_clicked();
    void fetchAllocationDetails();
private:
    Ui::LeaveEditor *ui;
    QSqlDatabase db;
    QString allocationID;
    QString currentID;
};

#endif // LEAVEEDITOR_H
