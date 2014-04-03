#ifndef MYMODELS_H
#define MYMODELS_H

#include <QSqlQueryModel>
#include <QSqlRecord>
#include "publics.h"

class AgeingModel : public QSqlQueryModel
{
	Q_OBJECT
public:
	explicit AgeingModel(QObject *parent = 0);

	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

class TransactionsModel : public QSqlQueryModel
{
	Q_OBJECT
public:
	explicit TransactionsModel(QObject *parent);
	QVariant data(const QModelIndex &index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};



#endif // MYMODELS_H
