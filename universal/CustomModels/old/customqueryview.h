#ifndef CUSTOMQUERYVIEW_H
#define CUSTOMQUERYVIEW_H

#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "datapublics.h"
namespace Ui {
class CustomQueryView;
}

class CustomQueryView : public QTreeView
{
    Q_OBJECT
    
public:
    explicit CustomQueryView(QWidget *parent = 0);
    ~CustomQueryView();
    void setModel(QAbstractItemModel *model);
    void setColumnHidden(int column, bool hide);
    void resizeColumnToContents(int column);
    void setQuery(QString query, QSqlDatabase database);
    void setQuery(QString query, QSqlDatabase database, QString reportTitle, bool reportFirstColumnHidden);
    QSqlQueryModel *myModel;
    QSortFilterProxyModel *filterModel;
    bool hideReportFirstColumn;
    QString str_ReportTitle;
    QString getCurrentID();
private slots:
    void on_trvTree_customContextMenuRequested(const QPoint &pos);    
    void on_trvTree_doubleClicked(const QModelIndex &index);
    void on_trvTree_clicked(const QModelIndex &index);
    void on_txtSearch_textChanged(const QString &arg1);
public slots:
    void actionRefresh();
    void actionExport();
    void actionPrint();
private:
    Ui::CustomQueryView *ui;
    QSqlDatabase db;
    QSqlQuery myQuery;
    QString queryString;

    QMenu *m_dropDownMenu;
    QAction *m_exportAction;
    QAction *m_printAction;
    QAction *m_refreshAction;
    QString originalQueryString;

    bool hasModel;
};

#endif // CUSTOMQUERYVIEW_H
