#ifndef IMS_KRACHARGES_H
#define IMS_KRACHARGES_H

#include <QDialog>
#include "datapublics.h"
namespace Ui {
class IMS_KraCharges;
}

class IMS_KraCharges : public QDialog
{
    Q_OBJECT
    
public:
    explicit IMS_KraCharges(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~IMS_KraCharges();
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::IMS_KraCharges *ui;
    QSqlDatabase db;
    QString currentID;
};

#endif // IMS_KRACHARGES_H
