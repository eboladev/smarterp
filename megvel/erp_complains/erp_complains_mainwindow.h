#ifndef ERP_COMPLAINS_MAINWINDOW_H
#define ERP_COMPLAINS_MAINWINDOW_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
namespace Ui {
class Erp_Complains_MainWindow;
}

class Erp_Complains_MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Erp_Complains_MainWindow(QWidget *parent = 0,
                                      QSqlDatabase database = QSqlDatabase());
    ~Erp_Complains_MainWindow();
    
private slots:
    void on_actionNew_Complain_triggered();

    void on_lstComplains_doubleClicked(const QModelIndex &index);

    void on_actionPrint_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::Erp_Complains_MainWindow *ui;
    QSqlDatabase db;
};

#endif // ERP_COMPLAINS_MAINWINDOW_H
