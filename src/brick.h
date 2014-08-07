#ifndef BRICK_H
#define BRICK_H
#include "square.h"

class brick
{
	square s1, s2, s3;
	int posX, posY;
	
	public:
		brick(int height = 3);
		void cycle(int dist = 1);
		int getX();
		int getY();
		

#endif
