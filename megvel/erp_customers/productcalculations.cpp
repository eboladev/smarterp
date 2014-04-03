#include "productcalculations.h"

ProductCalculations::ProductCalculations(QObject *parent) :
	QObject(parent)
{
}

void ProductCalculations::Calculations()
{
}

QString ProductCalculations::getSellingPrice()
{
	QString ret = "";

	return ret;
}

QString ProductCalculations::GetWeightKgs(QString qty)
{
	Q_UNUSED(qty);
	Calculations();
	return QString::number(BWEIGHT);
}

QString ProductCalculations::GetWeightTonnes(QString qty)
{
	Q_UNUSED(qty);
	Calculations();
	return QString::number(BWEIGHT / 1000);
}
