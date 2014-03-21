#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QDebug>
#include <QPen>

class GridScene : public QGraphicsScene
{
public:
    GridScene(qreal x, qreal y, qreal w,
              qreal h)
        : QGraphicsScene(x, y, w, h)
    {}

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) {
        qreal leftMargin = rect.left() + 50;
        qreal topMargin = rect.top() + 50;
        qreal rightMargin = rect.right() - 50;
        qreal bottomMargin = rect.bottom() - 50;

        //Draw title text
        QPen titlePen(Qt::darkBlue, 5);
        painter->setPen(titlePen);
        QRect titleRect(rect.left() + 2, rect.top()+ 2, 500, 50);
        painter->drawText(titleRect, Qt::AlignLeft, "Leave Allocation and usage: Joseph W Joshua");
        //Draw outside borders
        QVarLengthArray<QLineF, 100> borderLines;
        borderLines.append(QLineF(leftMargin, topMargin , leftMargin, bottomMargin)); //left border
        borderLines.append(QLineF(rightMargin, topMargin , rightMargin, bottomMargin)); //right border
        borderLines.append(QLineF(leftMargin, topMargin, rightMargin, topMargin)); //top border
        borderLines.append(QLineF(leftMargin, bottomMargin, rightMargin, bottomMargin)); //bottom border

        QPen borderPen(Qt::black, 4);
        painter->setPen(borderPen);
        painter->drawLines(borderLines.data(), borderLines.size());
    }


};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GridScene scene(0, 0, 800, 500);
    QGraphicsView view(&scene);
    //view.rotate(33);
    view.show();
    return a.exec();
}
