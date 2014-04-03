#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QSqlRecord>
namespace Ui {
class Inventory;
}

class Inventory : public QMainWindow
{
	Q_OBJECT

public:
	explicit Inventory(QWidget *parent = 0);
	~Inventory();


private slots:
	void on_trvInventory_itemDoubleClicked(QTreeWidgetItem *item, int column);

	void on_actionRefresh_triggered();

	void on_actionNew_triggered();

	void on_actionEdit_triggered();

	void on_trvInventory_itemClicked(QTreeWidgetItem *item, int column);

	void on_trvInventory_doubleClicked(const QModelIndex &index);

private:
	Ui::Inventory *ui;
	void reloadInventory();
	void addChildren(QString id, QTreeWidgetItem *parent);
	void setItem(QTreeWidgetItem *it, QSqlRecord rec);
	bool itemExists(QString id);
	QTreeWidgetItem *getItem(QString id);
	bool checkItemInParent(QString id, QTreeWidgetItem *parent);
	QTreeWidgetItem *getItemInParent(QString id, QTreeWidgetItem *parent);
	QString itemID;
};

#endif // INVENTORY_H
