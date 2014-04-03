
#include "barcodewidget.h"
#include "ean13.h"

BarCodeWidget::BarCodeWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(250, 250);
}

BarCodeWidget::~BarCodeWidget() {

}

void BarCodeWidget::draw(QPainter *painter) {
    painter->fillRect(painter->window(), Qt::lightGray);

    EAN13 code(reelNumber);

    painter->drawText(50, 40, "MEPCO 125K 1200");
    code.draw(QRectF(50, 50, 400, 200), *painter);

    //qreal scale = painter->device()->physicalDpiX() / 25.4;

    //code.draw(QRectF(50, 300, 37.29 * scale, 25.93 * scale), *painter);
}

void BarCodeWidget::paintEvent(QPaintEvent *event)
{
    event = event;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setViewport(0, 0, width(), width());

    draw(&painter);
}

void BarCodeWidget::refresh()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setViewport(0, 0, width(), width());

    draw(&painter);
}
