#include "mymodels.h"

AgeingModel::AgeingModel(QObject *parent) :
	QSqlQueryModel(parent)
{

}

QVariant AgeingModel::data(const QModelIndex &index, int role) const
{
	QVariant value = QSqlQueryModel::data(index, role);


	if (role == Qt::TextColorRole && index.column() > 0) {
		return qVariantFromValue(QColor(Qt::darkBlue));
	}

	if (role == Qt::DisplayRole && index.column() > 0) {
		QString txt = value.toString();
		//txt = QLocale(QLocale::English).toString(txt.toFloat());
		txt = QString("%L1").arg(txt.toDouble(), 2, 'f', 2);
		return txt;
	}

	if (role == Qt::TextAlignmentRole && index.column() > 0) {
		return Qt::AlignRight;
	}

	if (value.isValid() && role == Qt::DisplayRole) {
		return value.toString();
	}
	return value;
}

QVariant AgeingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal) {
		QVariant val = this->query().record().fieldName(section);
		if (section > 0 && role == Qt::TextAlignmentRole)
			return Qt::AlignRight;

		if (role == Qt::DisplayRole)
			return val;
	}
	return QAbstractItemModel::headerData(section, orientation, role);
}


TransactionsModel::TransactionsModel(QObject *parent)
{
}

QVariant TransactionsModel::data(const QModelIndex &index, int role) const
{
	QVariant value = QSqlQueryModel::data(index, role);

	if (role == Qt::BackgroundColorRole) {
		QModelIndex amountIndex = this->index(index.row(), 6);
		QVariant amt = QSqlQueryModel::data(amountIndex);
		if (amt.toString().startsWith("-")) {
			//This is a negative
			return  qVariantFromValue(QColor(235, 44, 6));
		} else {
			//Not a negative
			return  qVariantFromValue(QColor(6, 244, 125));
		}
	}

	if (role == Qt::DisplayRole && (index.column() == 6 || index.column() == 7)) {
		QString txt = value.toString();
		//txt = QLocale(QLocale::English).toString(txt.toLongLong());
		txt = QString("%L1").arg(txt.toDouble(), 2, 'f', 2);
		return txt;
	}

	if (role == Qt::TextAlignmentRole && (index.column() == 6 || index.column() == 7)) {
		return Qt::AlignRight;
	}

	if (role == Qt::DisplayRole && index.column() == 4) {
		QString dat = value.toString();
		QDate d = QDate::fromString(dat, "yyyy-MM-dd");
		return d.toString("dd-MMM-yyyy");
	}

	if (value.isValid() && role == Qt::DisplayRole) {
		return value.toString();
	}
	return value;
}

QVariant TransactionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal) {
		QVariant val = this->query().record().fieldName(section);
		qDebug() << val;
		if ((section == 6 || section == 7) && role == Qt::TextAlignmentRole)
			return Qt::AlignRight;

		if (role == Qt::DisplayRole)
			return val;
	}
	return QAbstractItemModel::headerData(section, orientation, role);
}
