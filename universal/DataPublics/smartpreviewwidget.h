#ifndef SMARTPREVIEWWIDGET_H
#define SMARTPREVIEWWIDGET_H

#include <QAbstractScrollArea>
#include <QDialog>
#if QT_VERSION >= 0x050000
#include <QtPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QPrinter>
#endif

class QAbstractScrollArea;
class ORODocument;

class SmartPreviewWidget : public QAbstractScrollArea
{
	Q_OBJECT
public:
	explicit SmartPreviewWidget(QWidget *parent=0);
	virtual ~SmartPreviewWidget();
	void loadReport(ORODocument *document, QPrinter *pPrinter);
	void updateView();
private slots:
	// zoom preview
	void zoomIn();
	void zoomOut();

private:
	virtual void paintEvent(QPaintEvent *e);
	virtual void resizeEvent(QResizeEvent *e);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	QRectF paperRect(QPaintDevice *device);
	int columnWidth();
	int nbColumns();

private:
	ORODocument * _doc;
	QPrinter *	_pPrinter;
	double _zoom;
	QPoint mousepos;
	QPoint scrollpos;

};

#endif // SMARTPREVIEWWIDGET_H
