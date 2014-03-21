#ifndef CashAdvancesWizard_H
#define CashAdvancesWizard_H

#include <QWizard>
#include <QtSql>
#include <QTreeWidget>

namespace Ui {
class CashAdvancesWizard;
}

class CashAdvancesWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit CashAdvancesWizard(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~CashAdvancesWizard();
    
private slots:
    void on_commandLinkButton_clicked();

    void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);

private:
    Ui::CashAdvancesWizard *ui;
    QSqlDatabase db;
};

#endif // CashAdvancesWizard_H
