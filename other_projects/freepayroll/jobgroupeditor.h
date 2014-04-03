#ifndef JOBGROUPEDITOR_H
#define JOBGROUPEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class JobGroupEditor;
}

class JobGroupEditor : public QDialog
{
	Q_OBJECT

public:
	explicit JobGroupEditor(QWidget *parent = 0);
	~JobGroupEditor();
	QSqlTableModel *model;
	QItemSelectionModel *selectionModel;
	QDataWidgetMapper *mapper;

	QSqlDatabase db;
private slots:
	void on_cmdNewJobGroup_clicked();
	void mapperChanged(int row);
	void on_lstJobGroups_clicked(const QModelIndex &index);

	void on_cmdSave_clicked();

	void on_cmdDeleteJobGroup_clicked();

private:
	Ui::JobGroupEditor *ui;

};

#endif // JOBGROUPEDITOR_H
