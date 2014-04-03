#ifndef SACCOPAYMENTEDITOR_H
#define SACCOPAYMENTEDITOR_H


#include <QtSql>
#include <QDialog>

namespace Ui {
class SaccoPaymentEditor;
}

class SaccoPaymentEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit SaccoPaymentEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~SaccoPaymentEditor();
    bool isAdding;
    QString currentID;
    void Edit(QString paymentID);
    void AddNew(QString employeeID);
private slots:
    void on_cmdSave_clicked();
private:
    Ui::SaccoPaymentEditor *ui;
    QSqlDatabase db;
};

#endif // SACCOPAYMENTEDITOR_H
