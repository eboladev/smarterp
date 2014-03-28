#ifndef PROFORMALIST_H
#define PROFORMALIST_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class ProformaList;
}

class ProformaList : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ProformaList(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~ProformaList();
    void setDatabase(QSqlDatabase database);
public slots:
    void reloadProformas();
private slots:
    void on_trvProformas_doubleClicked(const QModelIndex &index);

    void on_cmdPDF_clicked();

    void on_cmdPrintProforma_clicked();

    void on_cmdConfirmed_clicked();

    void on_cmdOpenUnPassedEntry_clicked();

    void uploadFile(QString fileType);
    void downloadFile(QString fileType);
    void on_cmdUploadUnPassedEntry_clicked();

    void on_cmdUploadPassedEntry_clicked();

    void on_cmdOpenPassedEntry_clicked();

    void on_cmdUploadSignedCompletedEntry_clicked();

    void on_cmdOpenSignedCompletedEntry_clicked();

    void on_cmdUploadDeliveryNote_clicked();

    void on_cmdOpenDeliveryNote_clicked();

private:
    Ui::ProformaList *ui;
    QSqlDatabase db;
};

#endif // PROFORMALIST_H
