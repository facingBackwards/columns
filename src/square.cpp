#include <cstdlib>
#include <iostream>
#include "square.h"

using namespace std;

square::square(int cols, int c)
{
	setRandColour(c);
	setPos((int)SQUARE_SIZE/2 + SQUARE_SIZE * (rand() % cols),(int)SQUARE_SIZE/2);
}

QRectF square::boundingRect() const
{
	return QRectF(-SQUARE_SIZE/2, -SQUARE_SIZE/2, SQUARE_SIZE, SQUARE_SIZE);
}

void square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush(QBrush(colour));
	painter->drawRect(-SQUARE_SIZE/2, -SQUARE_SIZE/2, SQUARE_SIZE, SQUARE_SIZE);
}

void square::setRandColour(int c)
{
	int x = rand() % c;
	intColour = x;
	switch (x)
	{
		case 0:
			colour = QColor(0,0,0xFF);
			break;
		case 1:
			colour = QColor(0,0xFF,0);
			break;
		case 2:
			colour = QColor(0xFF,0,0);
			break;
		case 3:
			colour = QColor(0xFF,0xFF,0);
			break;
		case 4:
			colour = QColor(0,0xFF,0xFF);
			break;
		case 5:
			colour = QColor(0xFF,0,0xFF);
			break;
		default:
			colour = QColor(0,0,0);
	}
}
