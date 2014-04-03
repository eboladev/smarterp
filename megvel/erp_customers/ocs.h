#ifndef OCS_H
#define OCS_H

#include <QMainWindow>
#include <QtSql>
#include <QSortFilterProxyModel>
namespace Ui {
class OCs;
}

class OCs : public QMainWindow
{
	Q_OBJECT

public:
	explicit OCs(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~OCs();

private:
	Ui::OCs *ui;
	QSqlDatabase db;
	QSqlQueryModel *ocModel;
private slots:
	void reloadOCS();
	void on_cmdRefresh_clicked();
	void on_treeView_doubleClicked(const QModelIndex &index);

public slots:
	void reloadCustomers();
};

#endif // OCS_H
