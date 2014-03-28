#ifndef CORRUGATORMW_H
#define CORRUGATORMW_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif
#include <QtSql>

#include <QMainWindow>
#include <QDialog>
#include <QWidget>

namespace Ui {
class CorrugatorMW;
}

class CorrugatorMW : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CorrugatorMW(QWidget *parent = 0);
    ~CorrugatorMW();
    
private:
    Ui::CorrugatorMW *ui;
    QSqlDatabase db;
    QString currentOcID;
    QString currentOcNo;
private slots:
    void reloadSchedule();
    void on_lstSchedule_clicked(const QModelIndex &index);
    void on_cmdSave_clicked();
};

#endif // CORRUGATORMW_H
