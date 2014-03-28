#ifndef PRINTOUTSETTINGSDIALOG_H
#define PRINTOUTSETTINGSDIALOG_H

#include <QDialog>
#include "sqlmodels.h"
namespace Ui {
class PrintoutSettingsDialog;
}

class PrintoutSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintoutSettingsDialog(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~PrintoutSettingsDialog();

private slots:
    void on_cmdAddField_clicked();

    void on_cmdSaveChanges_clicked();

    void on_cmdDelete_clicked();

    void on_cmdDefaults_clicked();

    void on_buttonBox_accepted();

    void on_cmdAddProfile_clicked();

private:
    Ui::PrintoutSettingsDialog *ui;
    SqlTableModel *model;
    void reloadFields();
    QSqlDatabase db;
};

#endif // PRINTOUTSETTINGSDIALOG_H
