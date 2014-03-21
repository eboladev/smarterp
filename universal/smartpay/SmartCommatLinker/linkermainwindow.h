#ifndef LINKERMAINWINDOW_H
#define LINKERMAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
namespace Ui {
class LinkerMainWindow;
}

class ODBCToMysqlImport;

class LinkerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LinkerMainWindow(QWidget *parent = 0);
    ~LinkerMainWindow();
protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void on_actionSettings_triggered();
    void linkerMessage(QString msg);
    void linkerError(QString err);
    void on_actionE_xit_triggered();

    void on_actionAbout_Smart_Commat_Linker_triggered();

    void toggleVisibility(QSystemTrayIcon::ActivationReason reason);
    void on_cmdFetchData_clicked();

    void onTimer();
private:
    Ui::LinkerMainWindow *ui;
    ODBCToMysqlImport *linker;

    QSystemTrayIcon *trayIcon;
};

#endif // LINKERMAINWINDOW_H
