#ifndef PRODUCTIONDATAENTRYMW_H
#define PRODUCTIONDATAENTRYMW_H

#include <QMainWindow>
#include <QtSql>
#include <QStyledItemDelegate>
namespace Ui {
class ProductionDataEntryMW;
}

class LockedEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    LockedEditDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

signals:

public slots:

};

class ProductionDataEntryMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductionDataEntryMW(QWidget *parent = 0);
    ~ProductionDataEntryMW();
private slots:
    void reloadSchedule();
    void on_dtpScheduleDate_dateChanged(const QDate &date);

    void on_actionPrint_Report_triggered();

private:
    Ui::ProductionDataEntryMW *ui;
    QSqlRelationalTableModel *model;
};

#endif // PRODUCTIONDATAENTRYMW_H
