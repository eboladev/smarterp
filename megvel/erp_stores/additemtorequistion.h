#ifndef ADDITEMTOREQUISTION_H
#define ADDITEMTOREQUISTION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AddItemToRequistion;
}

class AddItemToRequistion : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddItemToRequistion(QWidget *parent = 0);
    ~AddItemToRequistion();
    QString itemName;
    double qty;
    double unitPrice;
    double vat;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_cboItem_currentIndexChanged(const QString &arg1);

private:
    Ui::AddItemToRequistion *ui;
    QSqlDatabase db;
};

#endif // ADDITEMTOREQUISTION_H
