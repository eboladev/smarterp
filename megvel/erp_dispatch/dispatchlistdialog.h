#ifndef DISPATCHLISTDIALOG_H
#define DISPATCHLISTDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DispatchListDialog;
}

class DispatchListDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DispatchListDialog(QWidget *parent = 0, QString ticketNo = QString(),
                                QSqlDatabase db = QSqlDatabase()
                                );
    ~DispatchListDialog();
    
private:
    Ui::DispatchListDialog *ui;
};

#endif // DISPATCHLISTDIALOG_H
