#ifndef RVRSUPPLIEREDITOR_H
#define RVRSUPPLIEREDITOR_H

#include <QDialog>
#include <QtSql>



namespace Ui {
class RvrSupplierEditor;
}

class RvrSupplierEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit RvrSupplierEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~RvrSupplierEditor();
    void            Edit(QString supplierID);
    void            AddNew();
private slots:
    void on_cmdSave_clicked();

private:
    Ui::RvrSupplierEditor *ui;
    QSqlDatabase    db;
    QString         currentID;
    bool            isAdding;
};

#endif // RVRSUPPLIEREDITOR_H
