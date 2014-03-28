#ifndef STOREQUEUEMW_H
#define STOREQUEUEMW_H

#include <QMainWindow>
#include <QTimer>
#include <QtSql>

namespace Ui {
class StoreQueueMW;
}

class StoreQueueMW : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StoreQueueMW(QWidget *parent = 0);
    ~StoreQueueMW();
private slots:
    void onMinuteTimer();
    void onSecondTimer();
    void writeLog(QString msg);
private:
    Ui::StoreQueueMW *ui;
    QTimer *minuteTimer;

    QTimer *secondTimer;
    QSqlDatabase db;
};

#endif // STOREQUEUEMW_H
