#ifndef EDITREEL_H
#define EDITREEL_H

#include <QtSql>
#include <QDialog>

namespace Ui {
class EditReel;
}

class EditReel : public QDialog
{
	Q_OBJECT

public:
	explicit EditReel(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString reelID = QString());
	~EditReel();

private:
	Ui::EditReel *ui;
	QSqlDatabase db;
	QString currentID;
};

#endif // EDITREEL_H
