#ifndef OC_REEL_LINKING_H
#define OC_REEL_LINKING_H

#include <QtSql>

#include <QMainWindow>

namespace Ui {
class OC_Reel_Linking;
}

class OC_Reel_Linking : public QMainWindow
{
	Q_OBJECT

public:
	explicit OC_Reel_Linking(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~OC_Reel_Linking();

private:
	Ui::OC_Reel_Linking *ui;
	QSqlDatabase db;
};

#endif // OC_REEL_LINKING_H
