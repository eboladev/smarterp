#include "gtestmainwindow.h"
#include "ui_gtestmainwindow.h"



GTestMainWindow::GTestMainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::GTestMainWindow)
{
	ui->setupUi(this);

	QGraphicsScene *scene = new QGraphicsScene(this);
	CustomItem item = CustomItem(QRectF(75, 50, 30, 40), "TEST");

	scene->addItem(&item);
	ui->graphicsView->setScene(scene);

}

GTestMainWindow::~GTestMainWindow()
{
	delete ui;
}


CustomItem::CustomItem(const QRectF &rect, QString text)
{
	QGraphicsTextItem *textItem = new QGraphicsTextItem(this);
	textItem->setDefaultTextColor(QColor(255, 255, 255, 255));
	textItem->setPos(200, 200);
	textItem->setPlainText(text);
}

void CustomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(QBrush(QColor(21, 155, 210, 255)));
	painter->drawRect(boundingRect());
}
