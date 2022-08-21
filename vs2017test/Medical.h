#pragma once
#include "glut.h"

class Medical 
{
private:
	int x, y;
public:
	Medical(int x, int y);
	Medical();
	int getX() { return x; }
	int getY() { return y; }
	void DrawMe();
};