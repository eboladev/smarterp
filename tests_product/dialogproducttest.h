#ifndef DIALOGPRODUCTTEST_H
#define DIALOGPRODUCTTEST_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DialogProductTest;
}

class DialogProductTest : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogProductTest(QWidget *parent = 0);
    ~DialogProductTest();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogProductTest *ui;
    QSqlDatabase db;
};

#endif // DIALOGPRODUCTTEST_H
