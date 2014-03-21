#ifndef PASTENTRIESDIALOG_H
#define PASTENTRIESDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

class QSqlQueryModel;
class QSortFilterProxyModel;


namespace Ui {
class PastEntriesDialog;
}

class PastEntriesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PastEntriesDialog(QWidget *parent = 0, QSqlDatabase database
                               = QSqlDatabase()
                               );
    ~PastEntriesDialog();
    
private slots:
    void on_cmdSearch_clicked();

private:
    Ui::PastEntriesDialog *ui;
    QSqlDatabase db;

    QSqlQueryModel *model;
    QSortFilterProxyModel *filterModel;
};

#endif // PASTENTRIESDIALOG_H
