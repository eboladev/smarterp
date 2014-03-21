#ifndef LAUNCHERDIALOG_H
#define LAUNCHERDIALOG_H

#include <QDialog>
#include "updateservice.h"
namespace Ui {
class LauncherDialog;
}

class LauncherDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LauncherDialog(QWidget *parent = 0);
    ~LauncherDialog();
    
private:
    Ui::LauncherDialog *ui;

private slots:
    void newLogEntry(QString s);
    void startERP();

public slots:
    void closeAll();

signals:
    void emitCloseAll();
};

#endif // LAUNCHERDIALOG_H
