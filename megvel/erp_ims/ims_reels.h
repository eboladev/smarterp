#ifndef IMS_REELS_H
#define IMS_REELS_H

#include <QDialog>
#include "datapublics.h"
namespace Ui {
class IMS_Reels;
}

class IMS_Reels : public QDialog
{
	Q_OBJECT

public:
	explicit IMS_Reels(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~IMS_Reels();
	bool isAdding;
	QString reelID;
	QString containerID;
	void Edit();
private slots:
	void on_cmdSave_clicked();

private:
	Ui::IMS_Reels *ui;
	QSqlDatabase db;
};

#endif // IMS_REELS_H
