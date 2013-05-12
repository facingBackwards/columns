#include "columnsGame.h"
//#include <QMainWindow>

columnsGame::columnsGame(int w, int h)
{
	currentScore = 0;
	dim[0] = w * SQUARE_SIZE; dim[1] = h * SQUARE_SIZE;

	grid = new square*[w * h];

	scene = new QGraphicsScene(0,0,dim[0], dim[1]);
	scene->setBackgroundBrush(QColor(0xF0,0xED,0xB6));
	setupDisplay();
	view = new QGraphicsView(scene);
	setGeometry(2000,200,20 + dim[0], 20 + dim[1]);
	setCentralWidget(view);
}

void columnsGame::setupDisplay()
{
	scene->addRect(0,0,dim[0],dim[1]);
}
