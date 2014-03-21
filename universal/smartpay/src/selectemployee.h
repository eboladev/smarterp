#ifndef SELECTEMPLOYEE_H
#define SELECTEMPLOYEE_H

#include <QtSql>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
namespace Ui {
class SelectEmployee;
}

class SelectEmployee : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectEmployee(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~SelectEmployee();
    QString selectedEmployeeName;
    QString selectedEmployeeID;
private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::SelectEmployee *ui;
};

#endif // SELECTEMPLOYEE_H
