#ifndef SQUARE_H
#define SQUARE_H
#define SQUARE_SIZE 20
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class square : public QGraphicsItem
{
	private:
		QColor colour;

		void setRandColour(int c);
	public:
		square(int c = 6);//number of colour choices
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif
