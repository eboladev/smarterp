#ifndef PRODUCTION_REPORTS_H
#define PRODUCTION_REPORTS_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class production_reports;
}

class production_reports : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit production_reports(QWidget *parent = 0, QSqlDatabase d = QSqlDatabase());
    ~production_reports();
    
private slots:
    void on_cmdShow_clicked();

    void on_cmdShow_2_clicked();

private:
    Ui::production_reports *ui;
    QSqlDatabase db;
};

#endif // PRODUCTION_REPORTS_H
