#include "smartpreviewwidget.h"
#include "orprerender.h"
#include "orprintrender.h"
#include "renderobjects.h"

#include <QAbstractScrollArea>
#include <QAbstractTextDocumentLayout>
#include <QDebug>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScrollBar>
#include <QTextDocument>
#include <QTextFrame>
#include <QToolButton>
#include <QVBoxLayout>
#include <math.h>

// SmartPreviewWidget() ////////////////////////////////////////////////////////////
// constructor

const int spacing = 30;

SmartPreviewWidget::SmartPreviewWidget(QWidget *parent) :
    QAbstractScrollArea(parent)

{
    viewport()->setBackgroundRole(QPalette::Dark);
    verticalScrollBar()->setSingleStep(25);
    horizontalScrollBar()->setSingleStep(25);
}

void SmartPreviewWidget::loadReport(ORODocument *document, QPrinter *pPrinter)
{
    _doc = document;
    _pPrinter = pPrinter;
    _zoom = 1.0;
    updateView();
}
// ~SmartPreviewWidget() ///////////////////////////////////////////////////////////
// destructor

SmartPreviewWidget::~SmartPreviewWidget()
{
}

// updateView() ///////////////////////////////////////////////////////////////
// update the view
void SmartPreviewWidget::updateView()
{
    resizeEvent(0);
    viewport()->update();
}



// zoomIn() ///////////////////////////////////////////////////////////////////
// zoom in to view

void SmartPreviewWidget::zoomIn()
{
    _zoom += 0.2;
    // update
    resizeEvent(0);
    viewport()->update();

}

// zoomOut() //////////////////////////////////////////////////////////////////
// zoom out from view

void SmartPreviewWidget::zoomOut()
{
    _zoom = qMax(_zoom - 0.2, 0.2);
    // update
    resizeEvent(0);
    viewport()->update();
}

// mousePressEvent() //////////////////////////////////////////////////////////
// click to start view drag

void SmartPreviewWidget::mousePressEvent(QMouseEvent *e)
{
    mousepos = e->pos();
    scrollpos.rx() = horizontalScrollBar()->value();
    scrollpos.ry() = verticalScrollBar()->value();
    e->accept();
}

// mouseMoveEvent() ///////////////////////////////////////////////////////////
// drag view

void SmartPreviewWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousepos.isNull()) {
        e->ignore();
        return;
    }

    horizontalScrollBar()->setValue(scrollpos.x() - e->pos().x() + mousepos.x());
    verticalScrollBar()->setValue(scrollpos.y() - e->pos().y() + mousepos.y());
    horizontalScrollBar()->update();
    verticalScrollBar()->update();
    e->accept();
}

// mouseReleaseEvent() ////////////////////////////////////////////////////////
// release finished view drag

void SmartPreviewWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mousepos = QPoint();
    e->accept();
}

// paintEvent() ///////////////////////////////////////////////////////////////
// paint document on widget

void SmartPreviewWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());

    painter.translate(-horizontalScrollBar()->value(),
                      -verticalScrollBar()->value());
    painter.translate(spacing, spacing);

    double paperwidth = paperRect(viewport()).width();
    double paperheight = paperRect(viewport()).height();
    int nbCol = nbColumns();

    for(int page = 0; page < _doc->pages(); page++)
    {
        int column = page % nbCol;

        painter.save();
        painter.scale(_zoom, _zoom);

        // draw outline and shadow
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        painter.drawRect(QRectF(0, 0, paperwidth, paperheight));
        painter.setBrush(Qt::NoBrush);

        painter.drawLine(QLineF(paperwidth+1, 2, paperwidth+1, paperheight+2));
        painter.drawLine(QLineF(paperwidth+2, 2, paperwidth+2, paperheight+2));
        painter.drawLine(QLineF(2, paperheight+1, paperwidth, paperheight+1));
        painter.drawLine(QLineF(2, paperheight+2, paperwidth, paperheight+2));

        qreal xDpi = parentWidget()->logicalDpiX();
        qreal yDpi = parentWidget()->logicalDpiY();

        QSize margins(_pPrinter->paperRect().left() - _pPrinter->pageRect().left(), _pPrinter->paperRect().top() - _pPrinter->pageRect().top());

        ORPrintRender::renderPage(_doc, page, &painter, xDpi, yDpi, margins, 100);

        painter.restore();
        int xTranslation = column==nbCol-1 ? (columnWidth()* -(nbCol-1)) : columnWidth();
        int yTranslation = column==nbCol-1 ? (int)(spacing + paperRect(viewport()).height() * _zoom) : 0;
        painter.translate(xTranslation, yTranslation);
    }
}

// resizeEvent() //////////////////////////////////////////////////////////////
// view has resized

void SmartPreviewWidget::resizeEvent(QResizeEvent *)
{
    QSize docsize;
    const QSize viewsize = viewport()->size();

    docsize.setWidth(qRound(paperRect(viewport()).width() *
                            _zoom + 2 * spacing));

    int nbLines = (int)ceil ((double)_doc->pages() / (double)nbColumns());
    docsize.setHeight(qRound(nbLines * paperRect(viewport()).height() *
                             _zoom + (nbLines + 1) * spacing));

    horizontalScrollBar()->setRange(0, docsize.width() - viewsize.width());
    horizontalScrollBar()->setPageStep(viewsize.width());

    verticalScrollBar()->setRange(0, docsize.height() - viewsize.height());
    verticalScrollBar()->setPageStep(viewsize.height());

}

// paperRect() ////////////////////////////////////////////////////////////////
// Return the size of the paper, adjusted for DPI

QRectF SmartPreviewWidget::paperRect(QPaintDevice *device)
{
    // calculate size of paper
    QRectF rect = _pPrinter->paperRect();
    // adjust for DPI
    rect.setWidth(rect.width() *
        device->logicalDpiX() / _pPrinter->logicalDpiX());
    rect.setHeight(rect.height() *
        device->logicalDpiY() / _pPrinter->logicalDpiY());

    return rect;
}


int SmartPreviewWidget::columnWidth()
{
    return (int)(spacing + paperRect(viewport()).width() * _zoom);
}

int SmartPreviewWidget::nbColumns()
{
    int colWidth = columnWidth();
    int viewWidth = width() - spacing;
    return viewWidth<=colWidth ? 1 : viewWidth/colWidth;
}
