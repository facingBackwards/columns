#include <QApplication>
#include "columnsGame.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	columnsGame mainWin(6, 16);//create the game
	mainWin.show();
	return app.exec();
}

