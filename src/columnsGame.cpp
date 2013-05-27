#include "columnsGame.h"
#include <iostream>
#include <typeinfo>
#include <list>

using namespace std;
columnsGame::columnsGame(int w, int h, int c)
{
	//currentScore = 0;

	//rows = h; cols = w;
	dim[0] = w; dim[1] = h;
	colours = c;
	score = 0;
	colHeights = new int[w]();

	grid = new square*[w * h](); //array of squares
	matched = new int[w*h]();
	delay = new QTimer(this);

	scene = new QGraphicsScene(0,0,dim[0]*SQUARE_SIZE, dim[1]*SQUARE_SIZE);
	scene->setBackgroundBrush(QColor(0xF0,0xED,0xB6));
	setupDisplay();
	view = new QGraphicsView(scene);
	setGeometry(2000,200,20 + dim[0]*SQUARE_SIZE, 20 + dim[1]*SQUARE_SIZE);
	setCentralWidget(view);
	//grabKeyboard();
	//setEnabled(true);
	setFocus();

	addSquare();

	connect(delay, SIGNAL(timeout()), this, SLOT(gravity()));
	delay->start(GAME_SPEED);
}

void columnsGame::setupDisplay()
{
	scene->addRect(0,0,dim[0]*SQUARE_SIZE,dim[1]*SQUARE_SIZE);
}

void columnsGame::addSquare()
{
	newSquare = new square(dim[0], colours);
	scene->addItem(newSquare);
}

void columnsGame::gravity()
{
	int scoreChange = 0;
	if (newSquare->getY() < dim[1]-colHeights[newSquare->getX()] - 1)
	{
		lowerSquare(newSquare);
	}
	else
	{
		addSquareToGrid(newSquare);
		scoreChange = checkMatches();
		score += scoreChange;
		if (scoreChange)
		{
			removeMatches();
			//collapseMatches();
		}
		addSquare();
	}
}

void columnsGame::lowerSquare(square *current, int dist)
{
	current->setPos(current->pos().x(), current->pos().y() + SQUARE_SIZE*dist);
}

void columnsGame::moveSquare(square *current, int dir) //+ve is right, <0 left
{
	if (current->getX()<dim[0] && dir > 0 && colHeights[current->getX() + 1] < dim[1] - current->getY())
	{
		//move right
		current->setPos(current->pos().x() + SQUARE_SIZE, current->pos().y());
	}
	else if (current->getX()>0 && dir <=0 && colHeights[current->getX() - 1] < dim[1] - current->getY())
	{
		//move left
		current->setPos(current->pos().x() - SQUARE_SIZE, current->pos().y());
	}
}

void columnsGame::dropSquare(square* current)
{
	lowerSquare(current, dim[1] - colHeights[current->getX()] - current->getY() - 1);
}

void columnsGame::lowerPointer(int i, int dist)
{
	if (dist > 0)
	{
		grid[i+dist*dim[0]] = grid[i];
		grid[i] = 0;
	}
}

void columnsGame::addSquareToGrid(square *current)
{
	grid[current->getX() + dim[0]*current->getY()] = current;
//	cout << typeid(current).name() << "  " << current->getX() + dim[0]*current->getY() << "  " << current << endl;
	colHeights[current->getX()]++;
	if (colHeights[current->getX()] == dim[1])
	{
		cout << "height is " << colHeights[current->getX()] << endl;
		endGame();
	}
	newSquare = 0;
	return;
}

int columnsGame::checkMatches()
{
	int tmp;
	int scoreInc = 0; //score increase for this round
	delete[] matched;
	matched = new int[dim[0]*dim[1]]();
	for (int i = 0; i < dim[0]*dim[1]; i++)
	{
		if (grid[i] != NULL)
		{
			tmp = 0;
			tmp += ((i%dim[0] == 0) || (i%dim[0] == dim[0] - 1)) ? 1 : 0; //i is a side
			//cout << tmp << " " << dim[0]*dim[1] - dim[0] << endl;
			tmp += ((i<dim[0]) || (i>=(dim[0]*dim[1] - dim[0]))) ? 2 : 0; //i is top or bottom
			//cout << i << ": tmp=" << tmp << endl;

			switch (tmp)
			{
				case 0: //central squares -> three possible lines
					//cout << "case 0" << endl;
					scoreInc += checkHor(i);
					scoreInc += checkVer(i);
					scoreInc += checkUDiag(i);
					scoreInc += checkDDiag(i);
					break;

				case 1: //side squares -> one possible line
					//cout << "case 1" << endl;
					scoreInc += checkVer(i);
					break;

				case 2: // top/bottom -> one possible line
					//cout << "case 2" << endl;
					scoreInc += checkHor(i);
					break;

				case 3: //corners -> no lines
					//cout << "case 3" << endl;
					break;

				default: //should never happen
					break;
			}
			//cout << "hello world" << endl;
		}
	}
	if (scoreInc)
	{
		removeMatches();
		scoreInc += checkMatches();
	}
	return scoreInc;
}

int columnsGame::checkHor(int i)
{
	if (grid[i-1] != NULL && grid[i+1] != NULL)
	{
		if ((grid[i-1]->getIntColour() == grid[i]->getIntColour()) && (grid[i+1]->getIntColour() == grid[i]->getIntColour()))
		{
			matched[i-1]	= 1;
			matched[i]		= 1;
			matched[i+1]	= 1;
			//cout << i << ": hello World" << endl;
			return 1;
		}
	}
	return 0;
}

int columnsGame::checkVer(int i)
{
	if (grid[i-dim[0]] != NULL && grid[i+dim[0]] != NULL)
	{
		if ((grid[i-dim[0]]->getIntColour() == grid[i]->getIntColour()) && (grid[i+dim[0]]->getIntColour() == grid[i]->getIntColour()))
		{
			matched[i-dim[0]]	= 1;
			matched[i]			= 1;
			matched[i+dim[0]]	= 1;
			//cout << i << ": hello World" << endl;
			return 1;
		}
	}
	return 0;
}

int columnsGame::checkUDiag(int i)
{
	if (grid[i-dim[0]+1] != NULL && grid[i+dim[0]-1] != NULL)
	{
		if ((grid[i-dim[0]+1]->getIntColour() == grid[i]->getIntColour()) && (grid[i+dim[0]-1]->getIntColour() == grid[i]->getIntColour()))
		{
			matched[i-dim[0]+1]	= 1;
			matched[i]			= 1;
			matched[i+dim[0]-1]	= 1;
			return 1;
		}
	}
	return 0;
}

int columnsGame::checkDDiag(int i)
{
	if (grid[i-dim[0]-1] != NULL && grid[i+dim[0]+1] != NULL)
	{
		if ((grid[i-dim[0]-1]->getIntColour() == grid[i]->getIntColour()) && (grid[i+dim[0]+1]->getIntColour() == grid[i]->getIntColour()))
		{
			matched[i-dim[0]-1]	= 1;
			matched[i]			= 1;
			matched[i+dim[0]+1]	= 1;
			return 1;
		}
	}
	return 0;
}

void columnsGame::removeMatches()
{
	for (int i = 0; i < dim[0]*dim[1]; i++)
	{
		if (matched[i] == 1)
		{
			scene->removeItem(grid[i]);
			//scene->addItem(grid[i]);
			//scene->removeItem(grid[i]);
			delete grid[i];
			grid[i] = 0;
			matched[i] = 0;
		}
	}
	collapseMatches();
}

void columnsGame::collapseMatches()
{
	int tmpColHeight = 0;
	int tmpToDrop = 0;
	//char pause;
	//cin >> pause;
	for (int i = 0; i < dim[0]; i++)
	{
		tmpToDrop = 0;
		tmpColHeight = 0;
		for (int j = dim[1] -1; j > 0; j--)
		{
			//cout << i << "  " << j << endl;
			if (grid[i+dim[0]*j] != NULL)
			{
				tmpColHeight++;
				lowerSquare(grid[i+dim[0]*j], tmpToDrop);
				lowerPointer(i+dim[0]*j, tmpToDrop);
			}
			else
			{
				tmpToDrop++;
			}
		}
		//cout << "height of column: " << tmpColHeight << endl;
		colHeights[i] = tmpColHeight;
	}
	//showGrid();
	//cin >> pause;
	return;
}

void columnsGame::keyPressEvent(QKeyEvent *k)
{
	//Qt::Key keyIn = k;//->key();
	switch (k->key())
	{
		case Qt::Key_Left:
		{
			moveSquare(newSquare, -1);
			//cout << "hello Left"<< endl;
			break;
		}
		case Qt::Key_Right:
		{
			moveSquare(newSquare, 1);
			//cout << "hello Right"<< endl;
			break;
		}
		case Qt::Key_Down:
		{
			dropSquare(newSquare);
		}
		default:
		{
			return;
		}
	}
}

void columnsGame::endGame()
{
	cout << "end of game" <<endl;
	return;
}
//int columnsGame::getColumnHeight(int col)
//{
	//for (int i = dim[1]; i >0; i++)
	//{
		//if

void columnsGame::showGrid()
{
	cout << "_____" << endl;
	for (int i = 0; i < dim[1]; i++)
	{
		cout << '|';
		for (int j = 0; j < dim[0]; j++)
		{
			if (grid[j+dim[0]*i] != NULL)
			{
				cout<<grid[j+dim[0]*i]->getIntColour();
			}
			else
			{
				cout << ' ';
			}
		}
		cout << '|' << endl;
	}
	cout << "^^^^^^^^" << endl;
}
