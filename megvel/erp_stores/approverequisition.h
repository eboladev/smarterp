#ifndef APPROVEREQUISITION_H
#define APPROVEREQUISITION_H

#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class ApproveRequisition;
}

class ApproveRequisition : public QMainWindow
{
	Q_OBJECT

public:
	explicit ApproveRequisition(QWidget *parent = 0);
	~ApproveRequisition();

private:
	Ui::ApproveRequisition *ui;

private slots:
	void reloadNewRequisitions();
	void on_trvNewRequisitions_itemClicked(QTreeWidgetItem *item, int column);
	void reloadPostedRequisitions();
	void on_trvOldRequisitions_clicked(const QModelIndex &index);
	void on_cmdPost_clicked();
	void on_trvNewRequisitions_clicked(const QModelIndex &index);
};

#endif // APPROVEREQUISITION_H
