#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QMainWindow>
#include "lgmclientclass.h"
namespace Ui {
class TestMainWindow;
}

class TestMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TestMainWindow(QWidget *parent = 0);
    ~TestMainWindow();
    
private slots:
    void on_cmdSend_clicked();

private:
    Ui::TestMainWindow *ui;
    LGMClientClass *lgm;
};

#endif // TESTMAINWINDOW_H
