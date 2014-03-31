#ifndef FINISHING_REPORT_H
#define FINISHING_REPORT_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class finishing_report;
}

class finishing_report : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit finishing_report(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~finishing_report();
    
private slots:
    void on_cmdRefresh_clicked();
    void refresh();
private:
    Ui::finishing_report *ui;
    QSqlDatabase db;
};

#endif // FINISHING_REPORT_H
