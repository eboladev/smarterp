#include "overtime_threadedscanner.h"

Overtime_ThreadedScanner::Overtime_ThreadedScanner(QObject *parent, QSqlDatabase database, QString Month)
	: QThread(parent)
{
	Q_UNUSED(parent);
	db = database;
	monthID = Month;
}

void Overtime_ThreadedScanner::run()
{
}
