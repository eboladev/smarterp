#ifndef SUPPLIERIMPORTPROGRESSDIALOG_H
#define SUPPLIERIMPORTPROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class SupplierImportProgressDialog;
}

class SupplierImportProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierImportProgressDialog(QWidget *parent = 0, QString fileName = "C:\\Suppliers.xlsx");
    ~SupplierImportProgressDialog();
private slots:
    void threadMessage(QString msg);
    void threadError(QString msg);
private:
    Ui::SupplierImportProgressDialog *ui;
    QString path;
};

#endif // SUPPLIERIMPORTPROGRESSDIALOG_H
