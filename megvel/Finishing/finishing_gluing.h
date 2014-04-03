#ifndef FINISHING_GLUING_H
#define FINISHING_GLUING_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Finishing_Gluing;
}

class Finishing_Gluing : public QMainWindow
{
	Q_OBJECT

public:
	explicit Finishing_Gluing(QWidget *parent = 0,
				  QSqlDatabase database = QSqlDatabase()
			);
	~Finishing_Gluing();
private slots:
	void on_lstData_doubleClicked(const QModelIndex &index);

	void on_actionNew_Entry_triggered();
	void on_dtpDate_dateChanged(const QDate &date);

	void on_cmdDelete_clicked();

private:
	Ui::Finishing_Gluing *ui;
	QSqlDatabase db;
};

#endif // FINISHING_GLUING_H
