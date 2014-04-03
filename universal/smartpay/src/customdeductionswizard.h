#ifndef CUSTOMDEDUCTIONSWIZARD_H
#define CUSTOMDEDUCTIONSWIZARD_H

#include <QWizard>
#include <QtSql>
#include <QTreeWidget>

namespace Ui {
class CustomDeductionsWizard;
}

class CustomDeductionsWizard : public QWizard
{
	Q_OBJECT

public:
	explicit CustomDeductionsWizard(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~CustomDeductionsWizard();

private slots:
	void on_commandLinkButton_clicked();

	void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);

private:
	Ui::CustomDeductionsWizard *ui;
	QSqlDatabase db;
};

#endif // CUSTOMDEDUCTIONSWIZARD_H
