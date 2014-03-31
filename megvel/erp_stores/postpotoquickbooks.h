#ifndef POSTPOTOQUICKBOOKS_H
#define POSTPOTOQUICKBOOKS_H

#include <QObject>

class PostPOToQuickbooks : public QObject
{
    Q_OBJECT
public:
    explicit PostPOToQuickbooks(QObject *parent = 0);
    QString lastError;

private:
    QString ItemName;
signals:
    
public slots:
    
};

#endif // POSTPOTOQUICKBOOKS_H
