#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <QMainWindow>
#include <QtSql>
#include <QtGui>
namespace Ui {
class Employees;
}

class Employees : public QMainWindow
{
	Q_OBJECT

public:
	explicit Employees(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), bool AccessPayroll  = false);
	~Employees();
	void hideFinance();
	void hideHR();

	void reloadData();
private slots:
	void on_actionAdd_New_triggered();
	void on_actionSave_triggered();
	void on_treeView_clicked(const QModelIndex &index);
	void on_actionIssue_Advance_triggered();
	void on_AddAdvance_clicked();
	void on_DeleteAdvance_clicked();
	void on_NewSacco_clicked();
	void on_SaveSacco_clicked();
	void on_RemoveSacco_clicked();
	void on_SaccoTree_clicked(const QModelIndex &index);

	void on_actionDeactivate_triggered();


	void on_AddSaccoPayment_clicked();

	void on_DeleteSaccoPayment_clicked();

	void on_cmdDeleteBonus_clicked();

	void on_cmdAddBonus_clicked();

	void on_lstBonuses_doubleClicked(const QModelIndex &index);

	void on_lstSaccos_doubleClicked(const QModelIndex &index);

	void on_cmdAddOTHours_clicked();

	void on_cmdRemoveOTHours_clicked();

	void on_lstOvertimeHours_doubleClicked(const QModelIndex &index);

	void on_cmdAddHolidayHours_clicked();

	void on_cmdRemoveHolidayHours_clicked();

	void on_lstHolidayHours_doubleClicked(const QModelIndex &index);

	void on_cmdAddAbsentHours_clicked();

	void on_cmdRemoveAbsentHours_clicked();

	void on_lstAbsentHours_doubleClicked(const QModelIndex &index);

private:
	Ui::Employees   *ui;
	QSqlDatabase    db;
	bool            isAdding;
	void            reload();
	QString currentID;
	QString currentName;
	QSqlQueryModel *advancesModel;
	void reloadTrees();
	void reloadAdvances();
	void reloadSaccos();
	void loadSaccoList();
	void reloadBonuses();
	void reloadHours();

	void clearLineEdits(QObject *parent);
	void clearTexts();
	void loadCombos();

	bool isAclick;

	bool isSaccoAdding;
	QString currentSaccoID;
	QSqlQueryModel *saccoModel;

	bool payrollAccess;
public slots:
	void edit(QString employeeID);
	void addNew(QString employeeNo);
	void reloadAttendance();
	bool saveChanges(QString err = QString());
};

#endif // EMPLOYEES_H
