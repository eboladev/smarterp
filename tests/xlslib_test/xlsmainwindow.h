#ifndef XLSMAINWINDOW_H
#define XLSMAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class XLSMainWindow;
}

class XLSMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit XLSMainWindow(QWidget *parent = 0);
    ~XLSMainWindow();
    
private slots:
    void on_actionExecute_Query_triggered();
    void runQuery(QString query);
    void on_actionGenerate_Excel_FIle_triggered();

private:
    Ui::XLSMainWindow *ui;
    QSqlDatabase db;
    QSqlQueryModel *model;
};

#endif // XLSMAINWINDOW_H
