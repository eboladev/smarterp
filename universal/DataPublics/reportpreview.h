#ifndef REPORTPREVIEW_H
#define REPORTPREVIEW_H

#include <QMainWindow>
#include <QtGui>
#include <QMap>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport//QPrintPreviewWidget>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrintPreviewWidget>
#endif

#include <QtSql>
#include <QtXml>
namespace Ui {
class ReportPreview;
}

class ReportPreview : public QMainWindow
{
	Q_OBJECT

public:
	explicit ReportPreview(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ReportPreview();
	void setXML(QString xml);
public slots:
	void paintRequested(QPrinter* p);
private slots:
	void firstPage();
	void previousPage();
	void nextPage();
	void lastPage();
	void singlePage();
	void facingPages();
	void allPages();
	void zoomIn();
	void zoomOut();
	void print();

	void viewChanged();
private:
	Ui::ReportPreview *ui;
	QString _xml;
	QPrinter *printer;
	QPrintPreviewWidget *m_view;
	QSqlDatabase db;
protected:
	QDomDocument _doc;
};

#endif // REPORTPREVIEW_H
