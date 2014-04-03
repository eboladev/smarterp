#ifndef LEAVEDAYSWIZARD_H
#define LEAVEDAYSWIZARD_H

#include <QWizard>
#include <QTreeWidget>
#include <QtSql>
namespace Ui {
class LeaveDaysWizard;
}

class LeaveDaysWizard : public QWizard
{
	Q_OBJECT

public:
	explicit LeaveDaysWizard(QWidget *parent = 0, QSqlDatabase databse = QSqlDatabase());
	~LeaveDaysWizard();
private slots:
	void on_commandLinkButton_clicked();

	void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);
	void on_cboMonths_currentIndexChanged(const QString &arg1);

private:
	Ui::LeaveDaysWizard *ui;
	QSqlDatabase db;
};

#endif // LEAVEDAYSWIZARD_H
