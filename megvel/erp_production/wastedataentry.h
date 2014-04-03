#ifndef WASTEDATAENTRY_H
#define WASTEDATAENTRY_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class WasteDataEntry;
}

class WasteDataEntry : public QDialog
{
	Q_OBJECT

public:
	explicit WasteDataEntry(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~WasteDataEntry();
	bool isAdding;
	QString currentID;
	void AddNew();
	void edit();
private slots:
	void on_cmdSave_clicked();

private:
	Ui::WasteDataEntry *ui;
	QSqlDatabase db;
};

#endif // WASTEDATAENTRY_H
