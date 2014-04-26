#ifndef GTESTMAINWINDOW_H
#define GTESTMAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>


class CustomItem : public QGraphicsItem {
	Q_OBJECT

public:
	CustomItem(const QRectF &rect, QString text = "Item Text");
	void paint(QPainter *painter,
		   const QStyleOptionGraphicsItem *, QWidget *);
	QRectF boundingRect();
};

namespace Ui {
class GTestMainWindow;
}

class GTestMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit GTestMainWindow(QWidget *parent = 0);
	~GTestMainWindow();

private:
	Ui::GTestMainWindow *ui;
};

#endif // GTESTMAINWINDOW_H
