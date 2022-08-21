#include "Armory.h"

Armory::Armory(int x, int y)
{
	this->x = x;
	this->y = y;
}

Armory::~Armory()
{
}

void Armory::DrawMe()
{

	glColor3d(0.8, 0.8, 0.4); // brown
	glBegin(GL_POLYGON);
	glVertex2d(x - 1, y);
	glVertex2d(x - 1, y + 1);
	glVertex2d(x + 1, y + 1);
	glVertex2d(x + 1, y);
	glEnd();
	glColor3d(0, 0, 0); //frame
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 1, y);
	glVertex2d(x - 1, y + 1);
	glVertex2d(x + 1, y + 1);
	glVertex2d(x + 1, y);
	glEnd();

	glColor3d(0.3, 0.3, 0); // door
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.1, y);
	glVertex2d(x - 0.1, y + 0.5);
	glVertex2d(x + 0.1, y + 0.5);
	glVertex2d(x + 0.1, y);
	glEnd();
}
