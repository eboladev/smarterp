#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>
#include <QtSql>
#include <QtGui>


namespace Ui {
class TableEditor;
}

class TableEditor : public QDialog
{
	Q_OBJECT

public:
	explicit TableEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~TableEditor();
	void setTable(QString tableName, QString dbName);
private slots:
	void on_cmdCancel_clicked();

private:
	Ui::TableEditor *ui;
	QSqlDatabase db;
	QString _dbName;
	QString _tableName;

	void loadOriginalColumns();
};

#endif // TABLEEDITOR_H
