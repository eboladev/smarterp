#ifndef PRODUCTEDITOR_H
#define PRODUCTEDITOR_H

#include <QDialog>
#include "datapublics.h"
namespace Ui {
class ProductEditor;
}

class ProductEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProductEditor(QWidget *parent = 0);
    ~ProductEditor();
    void Edit(QString productID);
    void StartNew(QString customerID);
private slots:
    void on_cmdSave_clicked();
    void on_spinPricePerPiece_editingFinished();

    void on_spinPrice_editingFinished();

    void on_cboBottleName_currentIndexChanged(int index);
    void recalculatePrices();
    void on_spinBottlePrice_editingFinished();

    void on_chkBottles_toggled(bool checked);

    void on_cmdDelete_clicked();

signals:
    void changed();
private:
    Ui::ProductEditor *ui;
    bool isAdding;
    QSqlDatabase db;
    QString currentID;
};

#endif // PRODUCTEDITOR_H
