#ifndef BRANCHEDITOR_H
#define BRANCHEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
namespace Ui {
class BranchEditor;
}

class BranchEditor : public QDialog
{
	Q_OBJECT

public:
	explicit BranchEditor(QWidget *parent = 0);
	~BranchEditor();
	QSqlTableModel *model;
	QItemSelectionModel *selectionModel;
	QDataWidgetMapper *mapper;

	QSqlDatabase db;
private slots:
	void on_cmdNewBranch_clicked();
	void mapperChanged(int row);
	void on_lstBranches_clicked(const QModelIndex &index);

	void on_cmdSave_clicked();

	void on_cmdDeleteBranch_clicked();

private:
	Ui::BranchEditor *ui;

};

#endif // BRANCHEDITOR_H
