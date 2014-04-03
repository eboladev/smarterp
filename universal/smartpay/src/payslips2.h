#ifndef PAYSLIPS2_H
#define PAYSLIPS2_H

#include <QMainWindow>
#include <QtSql>
#include <QTreeWidget>
namespace Ui {
class Payslips2;
}

class Payslips2 : public QMainWindow
{
	Q_OBJECT

public:
	explicit Payslips2(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~Payslips2();

public slots:
	void reloadTree();

private slots:
	void on_cmdGenerate_clicked();
	void on_lstEmployees_itemChanged(QTreeWidgetItem *item, int column);

private:
	Ui::Payslips2 *ui;
	QSqlDatabase db;
};

#endif // PAYSLIPS2_H
