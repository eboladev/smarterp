#ifndef LEAVEDAYSWIZARD_H
#define LEAVEDAYSWIZARD_H

#include <QWizard>
#include <QTreeWidget>
#include <QtSql>
namespace Ui {
class TAWizard;
}

class TAWizard : public QWizard
{
	Q_OBJECT

public:
	explicit TAWizard(QWidget *parent = 0, QSqlDatabase databse = QSqlDatabase());
	~TAWizard();
private slots:
	void on_commandLinkButton_clicked();

	void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);
	void on_cboMonths_currentIndexChanged(const QString &arg1);

private:
	Ui::TAWizard *ui;
	QSqlDatabase db;
};

#endif // LEAVEDAYSWIZARD_H
