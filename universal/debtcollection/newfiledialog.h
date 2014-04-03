#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class NewFileDialog;
}

class NewFileDialog : public QDialog
{
	Q_OBJECT

public:
	explicit NewFileDialog(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~NewFileDialog();
	void Edit(QString id);
	void AddNew();
private slots:
	void on_cmdOK_clicked();

private:
	Ui::NewFileDialog *ui;
	QSqlDatabase db;
	bool isAdding;
	QString currentID;
};

#endif // NEWFILEDIALOG_H
