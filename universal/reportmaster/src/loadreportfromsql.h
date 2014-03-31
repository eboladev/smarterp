#ifndef LOADREPORTFROMSQL_H
#define LOADREPORTFROMSQL_H

#include <QDialog>
#include "datapublics.h"

namespace Ui {
class LoadReportFromSQL;
}

class LoadReportFromSQL : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoadReportFromSQL(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~LoadReportFromSQL();
    QString query;
    QString title;
    bool landscape;
    bool lines;
    bool pageNumbers;
    bool save;
private slots:
    void on_cmdPrintOnly_clicked();

    void on_cmdPrintAndSave_clicked();

private:
    Ui::LoadReportFromSQL *ui;
    QSqlDatabase db;
};

#endif // LOADREPORTFROMSQL_H
