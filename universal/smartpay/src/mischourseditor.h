#ifndef MISCHOURSEDITOR_H
#define MISCHOURSEDITOR_H


#include <QtSql>
#include <QDialog>

namespace Ui {
class MiscHoursEditor;
}

class MiscHoursEditor : public QDialog
{
	Q_OBJECT

public:
	explicit MiscHoursEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~MiscHoursEditor();
	bool isAdding;
	QString currentID;
	void Edit(QString miscID);
	void AddNew(QString employeeID, QString type);
private slots:
	void on_cmdSave_clicked();
private:
	Ui::MiscHoursEditor *ui;
	QSqlDatabase db;
};

#endif // MISCHOURSEDITOR_H
