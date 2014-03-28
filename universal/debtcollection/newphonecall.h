#ifndef NEWPHONECALL_H
#define NEWPHONECALL_H

#include <QDialog>
#include <QtSql>
namespace Ui {
class NewPhoneCall;
}

class NewPhoneCall : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewPhoneCall(QWidget *parent = 0);
    ~NewPhoneCall();
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::NewPhoneCall *ui;
};

#endif // NEWPHONECALL_H
