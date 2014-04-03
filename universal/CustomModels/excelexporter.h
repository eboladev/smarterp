#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H

#include <QObject>
#include <QtSql>
#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
class ExcelExporter : public QObject
{
    Q_OBJECT
public:
    explicit ExcelExporter(QObject *parent = 0, QSqlQueryModel *model = new QSqlQueryModel());
    
private:
    QSqlQueryModel *m_model;
    QString fileName;
    QProgressDialog *pdg;
signals:
    
public slots:
    void processingFinished();
    void status(QString s);
    void progress(int p);
};

#endif // EXCELEXPORTER_H
