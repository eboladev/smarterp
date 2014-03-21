#ifndef COL_INVOICELIST_H
#define COL_INVOICELIST_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class col_InvoiceList;
}

class col_InvoiceList : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit col_InvoiceList(QWidget *parent = 0);
    ~col_InvoiceList();
    
private slots:
    void on_cmdLoad_clicked();

private:
    Ui::col_InvoiceList *ui;
    QSqlDatabase odbc_db;
};

#endif // COL_INVOICELIST_H
