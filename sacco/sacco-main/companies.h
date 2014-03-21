#ifndef COMPANIES_H
#define COMPANIES_H
#include <QtSql>
#include <QMainWindow>

namespace Ui {
class Companies;
}

class Companies : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Companies(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Companies();
public slots:
    void refreshData();
private:
    Ui::Companies *ui;
    QSqlDatabase db;
};

#endif // COMPANIES_H
