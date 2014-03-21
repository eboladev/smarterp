#include "customersmodel.h"

CustomersModel::CustomersModel(QObject *parent) :
    QSqlQueryModel(parent)
{

}

QVariant CustomersModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    return value;
}
