#ifndef ADVANCESWIZARD_H
#define ADVANCESWIZARD_H

#include <QWizard>
#include <QtSql>
#include <QTreeWidget>

namespace Ui {
class AdvancesWizard;
}

class AdvancesWizard : public QWizard
{
    Q_OBJECT
    
public:
    explicit AdvancesWizard(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~AdvancesWizard();
    
private slots:
    void on_commandLinkButton_clicked();

    void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);

private:
    Ui::AdvancesWizard *ui;
    QSqlDatabase db;
};

#endif // ADVANCESWIZARD_H
