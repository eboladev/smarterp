#ifndef OCREGISTER_H
#define OCREGISTER_H

#include <QMainWindow>
#include <QtSql>


namespace Ui {
class OcRegister;
}

class OcRegister : public QMainWindow
{
	Q_OBJECT

public:
	explicit OcRegister(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~OcRegister();
	void setDatabase(QSqlDatabase database);
public slots:
	void on_cmdShowOcs_clicked();
	void on_lstOcs_doubleClicked(const QModelIndex &index);
private slots:
	void on_cmdPrint_clicked();
private:
	Ui::OcRegister *ui;
	QSqlDatabase db;
	QString query;
};


#endif // OCREGISTER_H
