#ifndef DATAENTRY_ADVANCES_H
#define DATAENTRY_ADVANCES_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class DataEntry_Advances;
}

class DataEntry_Advances : public QMainWindow
{
	Q_OBJECT

public:
	explicit DataEntry_Advances(QWidget *parent = 0, QSqlDatabase d = QSqlDatabase());
	~DataEntry_Advances();
private slots:
	void on_cmdNew_clicked();

	void on_cmdPrevious_clicked();

	void on_cmdNext_clicked();

	void on_cmdNewAdvance_clicked();

	void on_cmdDeleteAdvance_clicked();

	void on_cmdSave_clicked();

private:
	Ui::DataEntry_Advances *ui;
	QSqlDatabase db;
	void loadMaster(QString masterID);
	QString currentMasterID;
	void lockDataEntry(bool locked);
	QSqlRelationalTableModel *advanceModel;

	QSqlQuery masterQuery;
	void requeryMaster();
};

#endif // DATAENTRY_ADVANCES_H
