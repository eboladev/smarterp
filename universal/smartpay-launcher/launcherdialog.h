#ifndef LAUNCHERDIALOG_H
#define LAUNCHERDIALOG_H

#include <QDialog>

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
};

#endif // LAUNCHERDIALOG_H
