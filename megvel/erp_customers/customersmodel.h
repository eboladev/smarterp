#ifndef CUSTOMERSMODEL_H
#define CUSTOMERSMODEL_H

#include <QSqlQueryModel>
#include <QtSql>
class CustomersModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit CustomersModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
signals:
    
public slots:
    
};

#endif // CUSTOMERSMODEL_H
