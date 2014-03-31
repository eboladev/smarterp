#ifndef NEWREEL_H
#define NEWREEL_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class NewReel;
}

class NewReel : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewReel(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~NewReel();
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::NewReel *ui;
    QSqlDatabase db;
};

#endif // NEWREEL_H
