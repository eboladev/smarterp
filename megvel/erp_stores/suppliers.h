#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Suppliers;
}

class Suppliers : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Suppliers(QWidget *parent = 0);
    ~Suppliers();
    
private slots:
    void on_trvSuppliers_clicked(const QModelIndex &index);

    void on_cmdSave_clicked();

    void on_cmdAddNew_clicked();

    void on_cmdDelete_clicked();

private:
    Ui::Suppliers *ui;
    void reloadSuppliers();
    QSqlDatabase db;
    QString currentID;
    bool isAdding;
};

#endif // SUPPLIERS_H
