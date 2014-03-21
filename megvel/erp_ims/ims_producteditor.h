#ifndef IMS_PRODUCTEDITOR_H
#define IMS_PRODUCTEDITOR_H

#include <QDialog>
#include "datapublics.h"
namespace Ui {
class IMS_ProductEditor;
}

class IMS_ProductEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit IMS_ProductEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~IMS_ProductEditor();

    void AddNew(QString fileID);
    void Edit(QString productID);
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::IMS_ProductEditor *ui;
    QSqlDatabase db;
    bool isAdding;
    QString currentProductId;
    QString currentFileID;
};

#endif // IMS_PRODUCTEDITOR_H
