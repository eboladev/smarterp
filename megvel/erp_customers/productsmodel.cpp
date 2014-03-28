#include "productsmodel.h"

#include <QColor>
#include <QDebug>

ProductsModel::ProductsModel(QObject *parent) :
    QSqlQueryModel(parent)
{

}

QVariant ProductsModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (role == Qt::BackgroundColorRole) {
        QColor redColor(255, 114, 128);
        QColor greenColor(144, 238, 144);

        QString isApproved = item.model()->index(item.row(), 11).data().toString();
        if (isApproved == "Yes") {
            return QVariant::fromValue(greenColor);
        } else if (isApproved == "No"){
            return QVariant::fromValue(redColor);
        } else {
            return QSqlQueryModel::data(item, role);
        }
    }



    if (role == Qt::CheckStateRole && item.column() == 1) {
//        QString isApproved = item.model()->index(item.row(), 11).data().toString();
//        if (isApproved != "Yes") {
//            return Qt::Unchecked;
//        }
        if (checkedRows.contains(item.row()))
            return Qt::Checked;

        return Qt::Unchecked;
    }

    return value;
}

bool ProductsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() == 1 && role == Qt::CheckStateRole) {
        if (value == Qt::Checked) {
            checkedRows.append(index.row());
        } else {
            checkedRows.removeAll(index.row());
        }
        return true;
    }
    return QSqlQueryModel::setData(index, value, role);
}

Qt::ItemFlags ProductsModel::flags(const QModelIndex &index) const
{
    if (index.column() == 1) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }
    else
    {
        return QSqlQueryModel::flags(index);
    }
}

void ProductsModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    checkedRows.clear();
    return QSqlQueryModel::setQuery(query, db);
}

