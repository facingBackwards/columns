#ifndef COLUMNS_GAME_H
#define COLUMNS_GAME_H
#include <QtGui>
#include "square.h"

class columnsGame : public QMainWindow
{
	Q_OBJECT
	QGraphicsView *view;
	QGraphicsScene *scene;
	square **grid;
	int dim[2];
	int colours;
	QTimer *delay;
	square *newSquare;
	//int rows, cols;

	void setupDisplay();
	void addSquareToGrid(square *current);

	public:
		columnsGame(int w, int h, int c = 6);
		int currentScore;
		void addSquare();
		void lowerSquare(square* current);
	public slots:
		void gravity();

};

#endif
