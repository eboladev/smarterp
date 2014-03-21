#ifndef CONFIRMDELIVERY_H
#define CONFIRMDELIVERY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ConfirmDelivery;
}

class ConfirmDelivery : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfirmDelivery(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ConfirmDelivery();
    
private slots:
    void on_cmdConfirm_clicked();
    void reloadList();
private:
    Ui::ConfirmDelivery *ui;
    QSqlDatabase db;
};

#endif // CONFIRMDELIVERY_H
