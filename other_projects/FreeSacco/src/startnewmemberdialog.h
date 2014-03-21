#ifndef STARTNEWMEMBERDIALOG_H
#define STARTNEWMEMBERDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class StartNewMemberDialog;
}

class StartNewMemberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartNewMemberDialog(QWidget *parent = 0);
    ~StartNewMemberDialog();

private slots:
    void on_cmdSave_clicked();

private:
    Ui::StartNewMemberDialog *ui;
    QSqlDatabase db;
};

#endif // STARTNEWMEMBERDIALOG_H
