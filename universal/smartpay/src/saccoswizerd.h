#ifndef SACCOSWIZARD_H
#define SACCOSWIZARD_H

#include <QWizard>
#include <QtSql>
#include <QTreeWidget>

namespace Ui {
class SaccosWizard;
}

class SaccosWizard : public QWizard
{
	Q_OBJECT

public:
	explicit SaccosWizard(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~SaccosWizard();

private slots:
	void on_commandLinkButton_clicked();

	void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);

private:
	Ui::SaccosWizard *ui;
	QSqlDatabase db;
};

#endif // SACCOSWIZARD_H
