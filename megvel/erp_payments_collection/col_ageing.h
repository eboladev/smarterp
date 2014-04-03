#ifndef COL_AGEING_H
#define COL_AGEING_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Col_Ageing;
}

class Col_Ageing : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Col_Ageing(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
    ~Col_Ageing();
    
private slots:
    void on_cmdRecalculate_clicked();
    void reload();
    void on_lstAgeing_clicked(const QModelIndex &index);

private:
    Ui::Col_Ageing *ui;
    QSqlDatabase db;

    QString getHtmlForRange(QString rangeName, QDate startDate, QDate endDate, QString customerName);
};

#endif // COL_AGEING_H
