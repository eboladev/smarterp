#ifndef COMPANYMANAGER_H
#define COMPANYMANAGER_H

#include <QMainWindow>
#include "sqlmodels.h"
#include <QtSql>

namespace Ui {
class CompanyManager;
}

class CompanyManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit CompanyManager(QWidget *parent = 0);
    ~CompanyManager();

private slots:
    void on_cmdNewCompany_clicked();

    void on_cmdDeleteCompany_clicked();

    void on_cmdSaveCompany_clicked();

private:
    Ui::CompanyManager *ui;
    QSqlDatabase db;
    SqlTableModel *model;
    void loadCompanies();
};

#endif // COMPANYMANAGER_H
