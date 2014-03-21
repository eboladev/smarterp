#ifndef QUEUESERVERPREFERENCES_H
#define QUEUESERVERPREFERENCES_H

#include <QDialog>

namespace Ui {
class QueueServerPreferences;
}

class QueueServerPreferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit QueueServerPreferences(QWidget *parent = 0);
    ~QueueServerPreferences();
    
private:
    Ui::QueueServerPreferences *ui;
};

#endif // QUEUESERVERPREFERENCES_H
