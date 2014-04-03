#ifndef HTMLTOQTPRINTER_H
#define HTMLTOQTPRINTER_H
#include <QMainWindow>
#include <QtSql>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewWidget>
#include <QtPrintSupport/QPageSetupDialog>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewWidget>
#include <QPageSetupDialog>
#endif

#include <QActionGroup>
class HtmlToQtPrinter : public QObject
{
	Q_OBJECT
public:
	HtmlToQtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
			QSqlQuery query = QSqlQuery(),
			QString title = QString(""),
			bool firstColumnHidden = true,
			QString reportQuery = "SELECT (NOW)",
			QStringList columnsToSum = QStringList());

	HtmlToQtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
			QString query = QString(),
			QString title = QString(""),
			bool firstColumnHidden = true,
			QString reportQuery = "SELECT (NOW)",
			QStringList columnsToSum = QStringList());

	HtmlToQtPrinter(QWidget *parent = 0, QString html = QString());
public slots:
	void printRequested(QPrinter *prnt);

private:
	void print();

	QString fileName;
	QSqlDatabase db;
	QSqlQuery qu;
	QString s_query;
	QString s_title;
	bool rawHtml;
	QString s_rawHtml;
	bool hideFirstColumn;

	QPrintPreviewWidget *previewWidget;
	QPrinter *printer;
	QStringList sumColumns;

	QActionGroup *orientationGroup;

	QWidget *m_parent;
};

#endif // HTMLTOQTPRINTER_H
