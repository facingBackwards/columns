#include "columnsGame.h"

columnsGame::columnsGame(int w, int h, int c)
{
	currentScore = 0;

	//rows = h; cols = w;
	dim[0] = w * SQUARE_SIZE; dim[1] = h * SQUARE_SIZE;
	colours = c;

	grid = new square*[w * h];
	delay = new QTimer(this);

	scene = new QGraphicsScene(0,0,dim[0], dim[1]);
	scene->setBackgroundBrush(QColor(0xF0,0xED,0xB6));
	setupDisplay();
	view = new QGraphicsView(scene);
	setGeometry(2000,200,20 + dim[0], 20 + dim[1]);
	setCentralWidget(view);

	addSquare();

	connect(delay, SIGNAL(timeout()), this, SLOT(gravity()));
	delay->start(2);
}

void columnsGame::setupDisplay()
{
	scene->addRect(0,0,dim[0],dim[1]);
}

void columnsGame::addSquare()
{
	newSquare = new square(dim[0]/SQUARE_SIZE, colours);
	scene->addItem(newSquare);
}

void columnsGame::gravity()
{
	if (newSquare->pos().y() < dim[1] - SQUARE_SIZE/2)
	{
		lowerSquare(newSquare);
	}
	else
	{
		addSquareToGrid(newSquare);
		addSquare();
	}
}

void columnsGame::lowerSquare(square *current)
{
	current->setPos(current->pos().x(), current->pos().y() + SQUARE_SIZE);
}

void columnsGame::addSquareToGrid(square *current)
{
	return;
}
