#ifndef SALESREPS_H
#define SALESREPS_H

#include <QtSql>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

namespace Ui {
class SalesReps;
}

class SalesReps : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SalesReps(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~SalesReps();
    
private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_cmdAddNew_clicked();

private:
    Ui::SalesReps *ui;
    QSqlDatabase db;
    void reload();
};

#endif // SALESREPS_H
