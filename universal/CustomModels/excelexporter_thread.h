#ifndef EXCELEXPORTER_THREAD_H
#define EXCELEXPORTER_THREAD_H

#include <QThread>
#include <QtSql>

class ExcelExporter_Thread : public QThread
{
	Q_OBJECT
public:
	explicit ExcelExporter_Thread(QObject *parent = 0);
	void setVars(QSqlQueryModel *queryModel, QString fPath) { model = queryModel;  filePath = fPath;}
	void run();
private:
	QSqlQueryModel *model;
	QString filePath;
signals:
	void status(QString s);
	void progress(int p);
public slots:

};

#endif // EXCELEXPORTER_THREAD_H
