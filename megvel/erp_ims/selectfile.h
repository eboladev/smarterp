#ifndef SELECTFILE_H
#define SELECTFILE_H

#include "datapublics.h"
#include <QtGui>
#include <QtSql>


namespace Ui {
class SelectFile;
}

class SelectFile : public QDialog
{
	Q_OBJECT

public:
	explicit SelectFile(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~SelectFile();
	QString selectedFileId;
	QString selectedFileNo;
private slots:
	void on_cmdOk_clicked();

private:
	Ui::SelectFile *ui;
	QSqlDatabase db;
};

#endif // SELECTFILE_H
