#ifndef TABULAROCLINKING_H
#define TABULAROCLINKING_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "sqlmodels.h"
namespace Ui {
class TabularOcLinking;
}

class TabularOcLinking : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TabularOcLinking(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~TabularOcLinking();
    
private slots:
    void on_dtpDate_dateChanged(const QDate &date);

    void on_cmdPreviousDate_clicked();

    void on_cmdNextDate_clicked();

    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_Delete_triggered();

private:
    Ui::TabularOcLinking *ui;
    QSqlDatabase db;
    SqlTableModel *model;
};

#endif // TABULAROCLINKING_H
