#ifndef LPOOCLINKER_H
#define LPOOCLINKER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQueryModel>
namespace Ui {
class LPOOcLinker;
}

class LPOOcLinker : public QDialog
{
    Q_OBJECT
    
public:
    explicit LPOOcLinker(QWidget *parent = 0);
    ~LPOOcLinker();
    
    QString orderID() const;
    void setOrderID(const QString &orderID);

    QString customerName() const;
    void setCustomerName(const QString &customerName);

    QString orderNo() const;
    void setOrderNo(const QString &orderNo);

    void reloadOCs();
private slots:
    void on_cmdDownloadLPO_clicked();

    void on_cmdAddOc_clicked();

    void on_cmdRemoveSelected_clicked();

    void on_cmdSave_clicked();

private:
    Ui::LPOOcLinker *ui;

    QString m_orderID;
    QString m_customerName;
    QString m_orderNo;

    QSqlDatabase db;
    QSqlQueryModel *model;
};

#endif // LPOOCLINKER_H
