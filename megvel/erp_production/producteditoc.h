#ifndef PRODUCTEDITOC_H
#define PRODUCTEDITOC_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class ProductEditOC;
}

class ProductEditOC : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProductEditOC(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString ocNo = "");
    ~ProductEditOC();
private slots:
    void getDetails();
    void on_cmdSave_clicked();

private:
    Ui::ProductEditOC *ui;
    QSqlDatabase db;
    QString currentID;
};

#endif // PRODUCTEDITOC_H
