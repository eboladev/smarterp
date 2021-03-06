#ifndef FINISHING_STITCHING_H
#define FINISHING_STITCHING_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class Finishing_Stitching;
}

class Finishing_Stitching : public QMainWindow
{
	Q_OBJECT

public:
	explicit Finishing_Stitching(QWidget *parent = 0,
				     QSqlDatabase database = QSqlDatabase()
			);
	~Finishing_Stitching();
private slots:

	void on_lstData_doubleClicked(const QModelIndex &index);

	void on_actionNew_Entry_triggered();
	void on_dtpDate_dateChanged(const QDate &date);

	void on_cmdDelete_clicked();

private:
	Ui::Finishing_Stitching *ui;
	QSqlDatabase db;
};

#endif // FINISHING_STITCHING_H
