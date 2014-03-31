#ifndef QSMAINWINDOW_H
#define QSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class QSMainWindow;
}

class MailQueue;

class QSMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QSMainWindow(QWidget *parent = 0);
    ~QSMainWindow();
    
private slots:
    void on_cmdScan_clicked();
    void pingthreadMessage(QString msg);
    void pingthreadFailure();
    void pingThreadSuccess();

    void onMailLog(QString log);
    void on_cmdApportion_clicked();

private:
    Ui::QSMainWindow *ui;
    MailQueue *m_mailQueue;
};

#endif // QSMAINWINDOW_H
