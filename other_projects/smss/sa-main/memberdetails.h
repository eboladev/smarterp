#ifndef MEMBERDETAILS_H
#define MEMBERDETAILS_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MemberDetails;
}

class MemberDetails : public QMainWindow
{
	Q_OBJECT

public:
	explicit MemberDetails(QWidget *parent = 0);
	~MemberDetails();

private:
	Ui::MemberDetails *ui;
	QSqlDatabase db;
};

#endif // MEMBERDETAILS_H
