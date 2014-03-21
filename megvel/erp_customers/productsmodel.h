#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include <QSqlQueryModel>
#include <QtSql>
#include <QMap>

class ProductsModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ProductsModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    void setQuery(const QString &query, const QSqlDatabase &db);
private:
    QList<int> checkedRows;
signals:
    
public slots:
    
};


#endif // PRODUCTSMODEL_H
