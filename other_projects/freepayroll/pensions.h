#ifndef PENSIONEDITOR_H
#define PENSIONEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Ui {
class PensionEditor;
}

class PensionEditor : public QDialog
{
	Q_OBJECT

public:
	explicit PensionEditor(QWidget *parent = 0);
	~PensionEditor();
	QSqlTableModel *model;
	QItemSelectionModel *selectionModel;
	QDataWidgetMapper *mapper;

	QSqlDatabase db;
private slots:
	void on_cmdNewPension_clicked();
	void mapperChanged(int row);
	void on_lstPensions_clicked(const QModelIndex &index);

	void on_cmdSave_clicked();

	void on_cmdDeletePension_clicked();

private:
	Ui::PensionEditor *ui;

};

#endif // PENSIONEDITOR_H
