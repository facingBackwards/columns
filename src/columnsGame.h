#ifndef COLUMNS_GAME_H
#define COLUMNS_GAME_H
#include <QtGui>
#include "square.h"

class columnsGame : public QMainWindow
{
	Q_OBJECT
	QGraphicsView *view;
	QGraphicsScene *scene;
	square **grid;//store of pointers to squares
	int dim[2];//width x height in squares
	int colours; //number of colours to choose from
	int *colHeights; //array of height of squares in each column
	QTimer *delay;
	square *newSquare;
	int* matched; //to store queue of squares to be dropped
	int score;
	//int rows, cols;

	void setupDisplay();
	void addSquareToGrid(square *current);
	int checkMatches();
	void removeMatches();

	int checkVer(int i);
	int checkHor(int i);
	int checkUDiag(int i);
	int checkDDiag(int i);

	public:
		columnsGame(int w, int h, int c = 6);
		int currentScore;
		void addSquare();
		void lowerSquare(square* current);
		void endGame();
	public slots:
		void gravity();

};

#endif
