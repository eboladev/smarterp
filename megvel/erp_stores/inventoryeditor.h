#ifndef INVENTORYEDITOR_H
#define INVENTORYEDITOR_H

#include <QDialog>

namespace Ui {
class InventoryEditor;
}

class InventoryEditor : public QDialog
{
	Q_OBJECT

public:
	explicit InventoryEditor(QWidget *parent = 0, QString ItemID = "-1");
	~InventoryEditor();
	QString currentID;

	void Edit();
	void loadParentItems();
	void StartAddNew();
private:
	Ui::InventoryEditor *ui;
	bool isAdding;
private slots:
	void Save();
	void on_cmdDelete_clicked();
	void on_cmdSave_clicked();
};

#endif // INVENTORYEDITOR_H
