#ifndef DATAENTRY_NEWADVANCEMASTER_H
#define DATAENTRY_NEWADVANCEMASTER_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DataEntry_NewAdvanceMaster;
}

class DataEntry_NewAdvanceMaster : public QDialog
{
    Q_OBJECT
    
public:
    explicit DataEntry_NewAdvanceMaster(QWidget *parent = 0,
                                        QSqlDatabase d = QSqlDatabase());
    ~DataEntry_NewAdvanceMaster();
    QString masterID;
    
private slots:
    void on_cmdSave_clicked();

private:
    Ui::DataEntry_NewAdvanceMaster *ui;
    QSqlDatabase db;
};

#endif // DATAENTRY_NEWADVANCEMASTER_H
