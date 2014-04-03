#ifndef CUSTOMQUERYVIEW_H
#define CUSTOMQUERYVIEW_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtGui>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QtSql>
#include "datapublics.h"
#include "exportexcelobject.h"
#include <QModelIndex>
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
	void addColumnToSum(QString columnName);
	void addSumColumns(QStringList columnNames);
	void setSearchVisible(bool visible = true);
private slots:
	void on_trvTree_customContextMenuRequested(const QPoint &pos);
	void on_trvTree_doubleClicked(const QModelIndex &index);
	void on_trvTree_clicked(const QModelIndex &index);
	void on_txtSearch_textChanged(const QString &arg1);
	void on_cmdShowAll_clicked();
	void mySelectionChanged(QModelIndex &newItem);
public slots:
	void actionRefresh();
	void actionExport();
	void actionPrint();
signals:
	void myClicked(const QModelIndex &index);
private:
	Ui::CustomQueryView *ui;
	QSqlDatabase db;
	QSqlQuery myQuery;
	QString queryString;
	QString currentID;
	QMenu *m_dropDownMenu;
	QAction *m_exportAction;
	QAction *m_printAction;
	QAction *m_refreshAction;
	QString originalQueryString;

	bool hasModel;


	QStringList columnsToSum;
};

#endif // CUSTOMQUERYVIEW_H
