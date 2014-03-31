#ifndef HELPERDIALOG_H
#define HELPERDIALOG_H

#include <QWidget>

namespace Ui {
class HelperDialog;
}

class HelperDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit HelperDialog(QWidget *parent = 0);
    ~HelperDialog();
    
private slots:
    void on_cmdSave_clicked();

    void on_cmdAddMySqlServer_clicked();

private:
    Ui::HelperDialog *ui;
    void loadSettings();
};

#endif // HELPERDIALOG_H
