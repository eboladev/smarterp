#ifndef CREATEREGISTER_H
#define CREATEREGISTER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class CreateRegister;
}

class CreateRegister : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateRegister(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CreateRegister();
    
private slots:
    void on_cmdPreview_clicked();

    void on_cmdSave_clicked();

private:
    Ui::CreateRegister *ui;
    QSqlDatabase db;
};

#endif // CREATEREGISTER_H
