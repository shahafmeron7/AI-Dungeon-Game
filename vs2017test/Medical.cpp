#include "Medical.h"

Medical::Medical(int x, int y)
{
	this->x = x;
	this->y = y;
}

Medical::Medical()
{
}

void Medical::DrawMe()
{
	glColor3d(1, 1, 1); // brown
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

	glColor3d(1, 0, 0); // roof

	glBegin(GL_POLYGON);
	glVertex2d(x - 1, y + 1);
	glVertex2d(x + 1, y + 1);
	glVertex2d(x, y + 2);
	glEnd();
}
