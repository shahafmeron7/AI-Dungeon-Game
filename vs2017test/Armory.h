#pragma once
#include "Definitions.h"
#include "glut.h"


class Armory
{
private:
	int x, y;
public:
	Armory(int x, int y);
	~Armory();
	int getX() { return x; }
	int getY() { return y; }
	void DrawMe();
};
