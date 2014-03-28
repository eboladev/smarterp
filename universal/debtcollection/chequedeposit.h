#ifndef CHEQUEDEPOSIT_H
#define CHEQUEDEPOSIT_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ChequeDeposit;
}

class ChequeDeposit : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChequeDeposit(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString ID = QString());
    ~ChequeDeposit();
    void addCheque(QString chequeNo);
private slots:
    void on_cmdDeposit_clicked();

private:
    Ui::ChequeDeposit *ui;
    QSqlDatabase db;
    QString chequeID;
    QStringList chequeIDs;
};

#endif // CHEQUEDEPOSIT_H
