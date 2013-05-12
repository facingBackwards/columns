#include <QApplication>
#include "columnsGame.h"
//#define SQUARE_SIZE 20

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	columnsGame mainWin(6, 16);
	mainWin.show();
	return app.exec();
}

