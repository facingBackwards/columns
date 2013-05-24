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
		int intColour;

		void setRandColour(int c);
	public:
		square(int cols, int c = 6);//number of colour choices
		QRectF boundingRect() const;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		int getX() {return (int)(pos().x()-SQUARE_SIZE/2)/SQUARE_SIZE;}
		int getY() {return (int)(pos().y()-SQUARE_SIZE/2)/SQUARE_SIZE;}
		int getIntColour() {return intColour; }
};

#endif
