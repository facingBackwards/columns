#ifndef COLUMNS_GAME_H
#define COLUMNS_GAME_H
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "square.h"

#include <QWidget>
class columnsGame : public QMainWindow
{
	Q_OBJECT
	QGraphicsView *view;
	QGraphicsScene *scene;
	square **grid;
	int dim[2];

	void setupDisplay();

	public:
		columnsGame(int w, int h);
		int currentScore;
};

#endif
