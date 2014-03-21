#ifndef BARCODEWIDGET_H
#define BARCODEWIDGET_H

#if QT_VERSION >= 0x050000
    #include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
    #include <QtGui>
#endif

#include <QWidget>

class BarCodeWidget : public QWidget
{
    Q_OBJECT
public:
    BarCodeWidget(QWidget *parent = 0);
    ~BarCodeWidget();

    void draw(QPainter *painter);

protected:
    void paintEvent(QPaintEvent *event);

public:
    QString reelNumber;
    QString reel_type;
    QString size;
    QString supplier;

    void refresh();
};

#endif // BARCODEWIDGET_H
