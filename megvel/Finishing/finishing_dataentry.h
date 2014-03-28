#ifndef FINISHING_DATAENTRY_H
#define FINISHING_DATAENTRY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Finishing_DataEntry;
}

class Finishing_DataEntry : public QDialog
{
    Q_OBJECT
    
public:
    explicit Finishing_DataEntry(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Finishing_DataEntry();
    void AddNew(QString section, QDate date);
    void Edit(QString finishingID);
private slots:
    void on_cmdSave_clicked();

    void on_txtOrderNo_editingFinished();

private:
    Ui::Finishing_DataEntry *ui;
    QSqlDatabase db;
    bool isAdding;
    QString currentID;
    void updateOrderDetails();
};

#endif // FINISHING_DATAENTRY_H
