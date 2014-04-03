#ifndef REELALLOCATIONEDITOR_H
#define REELALLOCATIONEDITOR_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class ReelAllocationEditor;
}

class ReelAllocationEditor : public QDialog
{
	Q_OBJECT

public:
	explicit ReelAllocationEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ReelAllocationEditor();

private slots:
	void on_cmdSave_clicked();

private:
	Ui::ReelAllocationEditor *ui;
	QSqlDatabase db;
};

#endif // REELALLOCATIONEDITOR_H
