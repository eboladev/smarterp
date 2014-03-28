#ifndef NEWDISPATCHDIALOG_H
#define NEWDISPATCHDIALOG_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class NewDispatchDialog;
}

class NewDispatchDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewDispatchDialog(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~NewDispatchDialog();
    
private slots:
    void on_txtOcNo_textChanged(const QString &arg1);

    void on_cmdOK_clicked();

private:
    Ui::NewDispatchDialog *ui;
    QSqlDatabase db;
};

#endif // NEWDISPATCHDIALOG_H
