#ifndef QUEUECLIENTDIALOG_H
#define QUEUECLIENTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QFileSystemWatcher>
namespace Ui {
class QueueClientDialog;
}

class QueueClientDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QueueClientDialog(QWidget *parent = 0);
    ~QueueClientDialog();
private slots:
    void readSettings();
    void saveSettings();
private:
    Ui::QueueClientDialog *ui;
    QFileSystemWatcher *watch;
};

#endif // QUEUECLIENTDIALOG_H
