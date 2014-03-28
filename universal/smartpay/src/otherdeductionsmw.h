#ifndef OTHERDEDUCTIONSMW_H
#define OTHERDEDUCTIONSMW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class OtherDeductionsMW;
}

class OtherDeductionsMW : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OtherDeductionsMW(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~OtherDeductionsMW();
private slots:
    void reloadDeductions();
    void on_cboMonth_currentIndexChanged(const QString &arg1);

    void on_actionNew_Entries_triggered();

    void on_pushButton_clicked();

private:
    Ui::OtherDeductionsMW *ui;
    QSqlDatabase db;
};

#endif // OTHERDEDUCTIONSMW_H
