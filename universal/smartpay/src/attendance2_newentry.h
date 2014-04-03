#ifndef ATTENDANCE2_NEWENTRY_H
#define ATTENDANCE2_NEWENTRY_H

#include <QWizard>
#include <QtSql>

namespace Ui {
class Attendance2_NewEntry;
}

class Attendance2_NewEntry : public QWizard
{
	Q_OBJECT

public:
	explicit Attendance2_NewEntry(QWidget *parent = 0, QSqlDatabase d = QSqlDatabase());
	~Attendance2_NewEntry();

private slots:
	void reloadEmployees();
	void on_cmdReloadEmployees_clicked();
	void pageChanged(int pageNum);
	void on_cmdExit_clicked();

	void on_cmdStartOver_clicked();

	void on_cmdSave_clicked();

private:
	Ui::Attendance2_NewEntry *ui;
	QSqlDatabase db;
	bool saved;
};

#endif // ATTENDANCE2_NEWENTRY_H
