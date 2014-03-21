#include "datapublics.h"
#include "customqueryview.h"
#include "ui_customqueryview.h"
#include <QCursor>

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

    m_dropDownMenu->addAction(  m_refreshAction);
    m_dropDownMenu->addSeparator();
    m_dropDownMenu->addAction(  m_exportAction);
    m_dropDownMenu->addAction(  m_printAction);

    hideReportFirstColumn = true;
    str_ReportTitle = "";

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
        DataPublics::showWarning(db.lastError().text());
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

void CustomQueryView::actionExport()
{

}

void CustomQueryView::actionPrint()
{
    if (hasModel) {
        DataPublics::showReportPreview(DataPublics::getReportXML(queryString, str_ReportTitle, db, true, true, true, hideReportFirstColumn), db);
    }
}

void CustomQueryView::on_trvTree_doubleClicked(const QModelIndex &index)
{
    emit doubleClicked(index);
}

void CustomQueryView::on_trvTree_clicked(const QModelIndex &index)
{
    emit clicked(index);
}

QString CustomQueryView::getCurrentID()
{
    QString ret = "";
    ret = ui->trvTree->currentIndex().sibling(ui->trvTree->currentIndex().row(), 0).data().toString();
    return ret;
}

void CustomQueryView::on_txtSearch_textChanged(const QString &arg1)
{
    filterModel->setFilterRegExp(arg1);
    QString newQuery = originalQueryString;
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
    //qDebug() << newQuery;
}
