#ifndef QCDATAENTRY_H
#define QCDATAENTRY_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class QcDataEntry;
}

class QcDataEntry : public QDialog
{
	Q_OBJECT

public:
	explicit QcDataEntry(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~QcDataEntry();
	void setOc(QString oc);
private slots:
	void on_cmcSave_clicked();

private:
	Ui::QcDataEntry *ui;
	QSqlDatabase db;
	QString qcID;
	QString ocID;
};

#endif // QCDATAENTRY_H
