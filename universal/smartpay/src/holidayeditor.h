#ifndef HOLIDAYEDITOR_H
#define HOLIDAYEDITOR_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class HolidayEditor;
}

class HolidayEditor : public QDialog
{
	Q_OBJECT

public:
	explicit HolidayEditor(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~HolidayEditor();
	void Edit(QString id);
	void AddNew();
private slots:
	void on_cmdSave_clicked();

private:
	Ui::HolidayEditor *ui;
	QSqlDatabase db;
	QString currentID;
	bool isAdding;
};

#endif // HOLIDAYEDITOR_H
