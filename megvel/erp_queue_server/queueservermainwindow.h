#ifndef QUEUESERVERMAINWINDOW_H
#define QUEUESERVERMAINWINDOW_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>

#include <QMainWindow>
#include <QDialog>
#include <QLabel>

namespace Ui {
class QueueServerMainWindow;
}

class QueueServerMW : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QueueServerMW(QWidget *parent = 0);
    ~QueueServerMW();
    
private:
    Ui::QueueServerMainWindow *ui;
    QLabel *lbl_statusConnectivity;

private slots:
    void updateConnectivity();
};

#endif // QUEUESERVERMAINWINDOW_H
