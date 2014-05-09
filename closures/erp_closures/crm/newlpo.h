#ifndef NEWLPO_H
#define NEWLPO_H

#include <QtSql>
#include <QDialog>
#include <QTableWidgetItem>
namespace Ui {
class NewLPO;
}

class NewLPO : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewLPO(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString cID = QString()
                    );
    ~NewLPO();
    
private:
    Ui::NewLPO *ui;
    QSqlDatabase db;
    QString customerID;
    QStringList prodIDs;
    void setCustomer();
    void setProducts();
    bool isNew;
private slots:
    void uploadFile(QString columnName, QString fileNameCol, QString id, QString tableName, QString idCol);
    void on_toolButton_clicked();
    void recalculateRow(int r);
    void calculateTotals();
    void on_tblOrderDetails_cellChanged(int row, int column);
    void on_cmdPostOrder_clicked();
};

#endif // NEWLPO_H
