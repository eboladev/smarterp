#ifndef PAYROLLCONTAINER_H
#define PAYROLLCONTAINER_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class PayrollContainer;
}

class PayrollContainer : public QMainWindow
{
	Q_OBJECT

public:
	explicit PayrollContainer(QWidget *parent = 0, bool embedded = false,
				  QStringList companies = QStringList(),
				  QString user_id = QString()
				  );
	~PayrollContainer();
	QStringList selectedCompanies;
	QString userID;
private:
	Ui::PayrollContainer *ui;
	QSqlDatabase db;
	void logIn();
	bool bEmbed;
};

#endif // PAYROLLCONTAINER_H
