#ifndef SHIFTEDITOR_H
#define SHIFTEDITOR_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ShiftEditor;
}

class ShiftEditor : public QDialog
{
	Q_OBJECT

public:
	explicit ShiftEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ShiftEditor();
	void AddNew();
	void Edit(QString id);
private slots:
	void on_cmdSave_clicked();

private:
	QString currentID;
	bool isAdding;
	QSqlDatabase db;
	Ui::ShiftEditor *ui;
};

#endif // SHIFTEDITOR_H
