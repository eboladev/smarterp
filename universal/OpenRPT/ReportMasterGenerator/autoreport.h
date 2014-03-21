#ifndef AUTOREPORT_H
#define AUTOREPORT_H

#include <QDialog>
#include "datapublics.h"

namespace Ui {
class AutoReport;
}

class AutoReport : public QDialog
{
    Q_OBJECT
    
public:
    explicit AutoReport(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~AutoReport();
    
private slots:
    void on_cmdPreview_clicked();

    void on_cmdGenerateReport_clicked();

private:
    Ui::AutoReport *ui;
    QSqlDatabase db;
    QSqlQueryModel *dataModel;
};

#endif // AUTOREPORT_H
