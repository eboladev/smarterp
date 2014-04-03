#include "customqueryview.h"
#include "ui_customqueryview.h"
#include <QCursor>

#include "htmlreportpreview.h"
#include "htmlprinter.h"
CustomQueryView::CustomQueryView(QWidget *parent) :
	QTreeView(parent),
	ui(new Ui::CustomQueryView)
{
	ui->setupUi(this);

	filterModel = new QSortFilterProxyModel(parent);
	hasModel = false;
	m_dropDownMenu = new QMenu(this);

	m_printAction = new QAction("&Print", this);
	m_refreshAction = new QAction("&Refresh", this);
	m_exportAction = new QAction("&Export", this);

	connect (m_printAction, SIGNAL(triggered()), SLOT(actionPrint()));
	connect (m_refreshAction, SIGNAL(triggered()), SLOT(actionRefresh()));
	connect (m_exportAction, SIGNAL(triggered()), SLOT(actionExport()));

	m_dropDownMenu->addAction(m_refreshAction);
	m_dropDownMenu->addSeparator();
	m_dropDownMenu->addAction(m_exportAction);
	m_dropDownMenu->addAction(m_printAction);

	hideReportFirstColumn = true;
	str_ReportTitle = "";

	ui->lblLST->setVisible(false);

	connect (ui->trvTree->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
		 this, SLOT(mySelectionChanged(QModelIndex*)));

	//connect (ui->trvTree, SIGNAL(clicked(QModelIndex)), this, SLOT(mySelectionChanged(QModelIndex&)));
}

CustomQueryView::~CustomQueryView()
{
	delete ui;
}

void CustomQueryView::setModel(QAbstractItemModel *model)
{
	ui->trvTree->setModel(model);
	hasModel = true;
}

void CustomQueryView::setColumnHidden(int column, bool hide)
{
	ui->trvTree->setColumnHidden(column, hide);
}

void CustomQueryView::resizeColumnToContents(int column)
{
	ui->trvTree->resizeColumnToContents(column);
}

void CustomQueryView::setQuery(QString query, QSqlDatabase database)
{
	queryString = query;
	originalQueryString = queryString;
	db = database;
	myQuery = db.exec(query);
	if (db.lastError().isValid()) {
		QMessageBox::warning(this, "Warning", db.lastError().text());
		return;
	}
	myModel = new QSqlQueryModel(this);
	myModel->setQuery(myQuery);
	filterModel->setSourceModel(myModel);
	filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);
	filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	filterModel->setFilterKeyColumn(-1);
	setModel(filterModel);
}

void CustomQueryView::setQuery(QString query, QSqlDatabase database, QString reportTitle, bool reportFirstColumnHidden)
{
	str_ReportTitle = reportTitle;
	hideReportFirstColumn = reportFirstColumnHidden;
	setQuery(query, database);
}

void CustomQueryView::on_trvTree_customContextMenuRequested(const QPoint &pos)
{
	Q_UNUSED(pos);
	m_dropDownMenu->popup(QCursor::pos());
}

void CustomQueryView::actionRefresh()
{
	if (hasModel) {
		setQuery(queryString, db);
	}
}

#include "exportexcelobject.h"
#include "excelexporter.h"
void CustomQueryView::actionExport()
{
	QInputDialog *dg = new QInputDialog(this);
	QStringList lst;
	lst << "Microsoft Excel XML(2007 Onwards)";
	dg->setComboBoxItems(lst);
	QString opt = dg->getItem(this, "Format", "Select a format to export to.", lst, 0, false);
	if (opt.length() > 0) {
		if (opt.contains("Microsoft Excel")) {
			ExcelExporter *ex = new ExcelExporter(this, myModel);
			Q_UNUSED(ex);
		}
	}
}

void CustomQueryView::actionPrint()
{
	if (hasModel) {
		//DataPublics::showReportPreview(DataPublics::getReportXML(queryString, str_ReportTitle, db, true, true, true, hideReportFirstColumn), db);
		//qDebug() << "query: " << queryString;
		//HTMLReportPreview *pv = new HTMLReportPreview(this, db, myQuery, str_ReportTitle, hideReportFirstColumn, queryString, columnsToSum);
		//pv->show();
		DataPublics::htmlToQtPrinter(this, db, myQuery, str_ReportTitle, hideReportFirstColumn, queryString, columnsToSum);
		//HtmlPrinter(this, db, queryString, str_ReportTitle);
	}
}

void CustomQueryView::on_trvTree_doubleClicked(const QModelIndex &index)
{
	emit doubleClicked(index);
}

void CustomQueryView::on_trvTree_clicked(const QModelIndex &index)
{
	currentID = index.model()->index(index.row(), 0).data().toString();
	emit clicked(index);
}

QString CustomQueryView::getCurrentID()
{
	return currentID;
}

void CustomQueryView::addColumnToSum(QString columnName)
{
	columnsToSum.append(columnName);
}

void CustomQueryView::addSumColumns(QStringList columnNames)
{
	columnsToSum.append(columnNames);
}

void CustomQueryView::setSearchVisible(bool visible)
{
	ui->txtSearch->setVisible(visible);
}

void CustomQueryView::on_txtSearch_textChanged(const QString &arg1)
{
	filterModel->setFilterRegExp(arg1);
	QString newQuery = originalQueryString;
	myModel->setQuery(originalQueryString);
	QString where = " WHERE (";
	QSqlRecord rec = myModel->record();
	for (int c = 0; c < myModel->columnCount(); c++) {
		if (c > 0)
		{
			where.append("\n OR `");
		} else {
			where.append("\n`");
		}
		where.append(rec.fieldName(c) + "` LIKE '%" + arg1 + "%' ");
	}
	where.append(")");
	if (newQuery.contains("WHERE")) {
		newQuery.replace("WHERE", where + " AND ");
	} else {
		newQuery.append(where);
	}
	//DataPublics::showInformation(newQuery);
	queryString = newQuery;
	qDebug() << newQuery;
}

void CustomQueryView::on_cmdShowAll_clicked()
{
	ui->txtSearch->setText("");
	setQuery(originalQueryString, db, str_ReportTitle, hideReportFirstColumn);
}

void CustomQueryView::mySelectionChanged(QModelIndex &newItem)
{
	currentID = newItem.model()->index(newItem.row(), 0).data().toString();
	on_trvTree_clicked(newItem);
}
