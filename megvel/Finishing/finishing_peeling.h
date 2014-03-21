#ifndef FINISHING_PEELING_H
#define FINISHING_PEELING_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Finishing_Peeling;
}

class Finishing_Peeling : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Finishing_Peeling(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Finishing_Peeling();
    
private slots:


    void on_lstData_doubleClicked(const QModelIndex &index);

    void on_actionNew_Entry_triggered();

    void on_dtpDate_dateChanged(const QDate &date);

    void on_cmdDelete_clicked();

private:
    Ui::Finishing_Peeling *ui;
    QSqlDatabase db;
};

#endif // FINISHING_PEELING_H
