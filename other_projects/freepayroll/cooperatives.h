#ifndef COOPERATIVEEDITOR_H
#define COOPERATIVEEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class CooperativeEditor;
}

class CooperativeEditor : public QDialog
{
	Q_OBJECT

public:
	explicit CooperativeEditor(QWidget *parent = 0);
	~CooperativeEditor();
	QSqlTableModel *model;
	QItemSelectionModel *selectionModel;
	QDataWidgetMapper *mapper;

	QSqlDatabase db;
private slots:
	void on_cmdNewCooperative_clicked();
	void mapperChanged(int row);
	void on_lstCooperatives_clicked(const QModelIndex &index);

	void on_cmdSave_clicked();

	void on_cmdDeleteCooperative_clicked();

private:
	Ui::CooperativeEditor *ui;

};

#endif // COOPERATIVEEDITOR_H
