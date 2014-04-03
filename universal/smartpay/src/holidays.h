#ifndef HOLIDAYS_H
#define HOLIDAYS_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class Holidays;
}

class Holidays : public QWidget
{
	Q_OBJECT

public:
	explicit Holidays(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~Holidays();

private slots:
	void on_cmdAddNew_clicked();

	void on_lstHolidays_clicked(const QModelIndex &index);

	void on_lstHolidays_doubleClicked(const QModelIndex &index);

	void on_cmdDelete_clicked();

private:
	Ui::Holidays *ui;
	QSqlDatabase db;
	void reloadHolidays();
};

#endif // HOLIDAYS_H
