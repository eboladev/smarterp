#ifndef SALESREPEDITOR_H
#define SALESREPEDITOR_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QtSql>
#include <QMainWindow>
#include <QDialog>
namespace Ui {
class SalesRepEditor;
}



class SalesRepEditor : public QDialog
{
	Q_OBJECT

public:
	explicit SalesRepEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~SalesRepEditor();
	QString currentId;
	void addNew();
	void edit();
private slots:
	void on_cmdSave_clicked();

	void on_cmdDelete_clicked();

	void on_cmdClose_clicked();

private:
	Ui::SalesRepEditor *ui;
	QSqlDatabase db;
	bool isAdding;
};

#endif // SALESREPEDITOR_H
