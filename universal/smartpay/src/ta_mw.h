#ifndef TA_MW_H
#define TA_MW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class TaMW;
}

class TaMW : public QMainWindow
{
	Q_OBJECT

public:
	explicit TaMW(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~TaMW();

private slots:
	void on_cboMonths_editTextChanged(const QString &arg1);

	void on_actionNew_triggered();

	void on_cmdDelete_clicked();

	void on_cboMonths_currentIndexChanged(const QString &arg1);

private:
	Ui::TaMW *ui;
	QSqlDatabase db;
};

#endif // TA_MW_H
