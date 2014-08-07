#ifndef COLUMNS_GAME_H
#define COLUMNS_GAME_H
#include <QtGui>
#include "square.h"
#include "settings.h"

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
	bool match;
	//int rows, cols;

	void setupDisplay();
	void addSquareToGrid(square *current);
	int checkMatches();
	void removeMatches();
	void collapseMatches();

	//controls
	void keyPressEvent(QKeyEvent *key);

	//functions to check for matches around square i
	int checkVer(int i);
	int checkHor(int i);
	int checkUDiag(int i);
	int checkDDiag(int i);

	void showGrid(); //debug function to show positions of squares

	public:
		columnsGame(int w, int h, int c = GAME_COLOURS);
		//int currentScore;
		void addSquare();
		void lowerSquare(square* current, int dist = 1);
		void moveSquare(square* current, int dir);
		void dropSquare(square* current);
		void lowerPointer(int i, int dist = 1);
		void endGame();
	public slots:
		void gravity();

};

#endif
