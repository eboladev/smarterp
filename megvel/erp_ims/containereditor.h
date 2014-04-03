#ifndef CONTAINEREDITOR_H
#define CONTAINEREDITOR_H

#include <QDialog>
#include "datapublics.h"
namespace Ui {
class ContainerEditor;
}

class ContainerEditor : public QDialog
{
	Q_OBJECT

public:
	explicit ContainerEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ContainerEditor();
	bool isAdding;
	QString currentID;
	QString shipmentID;
	void Edit(QString sID);
private slots:
	void on_cmdSave_clicked();

	void on_cmdAddReel_clicked();

	void on_cmdRemoveReel_clicked();

	void on_lstReels_doubleClicked(const QModelIndex &index);

	void on_cmdPostToReelStock_clicked();

private:
	Ui::ContainerEditor *ui;
	QSqlDatabase db;
	void loadReels();

};

#endif // CONTAINEREDITOR_H
