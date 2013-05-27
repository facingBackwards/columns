#include <QApplication>
//#include "settings.h"
#include "columnsGame.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	columnsGame mainWin(GAME_COLUMNS, GAME_ROWS);//create the game
	mainWin.show();
	return app.exec();
}

