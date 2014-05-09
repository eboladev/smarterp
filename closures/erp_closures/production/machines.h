#ifndef MACHINES_H
#define MACHINES_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Machines;
}

class Machines : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Machines(QWidget *parent = 0);
    ~Machines();
    
private slots:
    void newRow();
    void reloadMachines();
    void on_actionRefresh_triggered();

    void on_cmdDelete_clicked();

private:
    Ui::Machines *ui;
    QSqlTableModel *model;
};

#endif // MACHINES_H
