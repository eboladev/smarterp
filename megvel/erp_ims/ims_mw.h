#ifndef IMS_MW_H
#define IMS_MW_H

#include <QMainWindow>
#include "datapublics.h"

namespace Ui {
class ims_mw;
}

class ims_mw : public QMainWindow
{
	Q_OBJECT

public:
	explicit ims_mw(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ims_mw();

private:
	Ui::ims_mw *ui;
	QSqlDatabase db;
};

#endif // IMS_MW_H
