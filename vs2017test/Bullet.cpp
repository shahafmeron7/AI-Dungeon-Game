#include "Bullet.h"
#include "glut.h"
#include <math.h>
#include <string>


Bullet::Bullet()
{
	isMoving = false;

}

// angle must be in radians
Bullet::Bullet(double x, double y, double angle)
{
	this->x = x;
	this->y = y;
	direction_angle = angle;
	bulletHitEnemy = false;
	isMoving = false;
}

void Bullet::show()
{
	glColor3d(0, 0, 0);
	glBegin(GL_POLYGON);
		glVertex2d(x - 0.5, y);
		glVertex2d(x , y + 0.5);
		glVertex2d(x + 0.5, y);
		glVertex2d(x , y - 0.5);
	glEnd();
}


Bullet::~Bullet()
{
}

void Bullet::Move(int maze[MSZ][MSZ], int targetColor, vector<NPC*> &team, vector<NPC*> &enemyTeam)
{
	double dx, dy;
	string teamString = targetColor == PURPLE_TEAM ? "Purple Team" : "Green Team";
	if (isMoving)
	{
		dx = cos(direction_angle);
		dy = sin(direction_angle);
		x += dx * BULLET_SPEED;
		y += dy * BULLET_SPEED;
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			if (enemyTeam.at(i) != nullptr) {

				int enemyCol = enemyTeam.at(i)->getCol();
				int enemyRow = enemyTeam.at(i)->getRow();
				//check if bullet near enemy, so need to take hit
				if (fabs(x - enemyCol) <= 1.5 && fabs(y - enemyRow) <= 1.5) {
					//if the enemy is dead, updating to null
					if (enemyTeam.at(i)->gotHit()) {
						enemyTeam.at(i) = nullptr;
						cout << "Soldier Number " << i << " From " << teamString << " Is Dead" << endl;
					}
					//else soldier got hit minus 50hp
					else {
						cout << "Soldier Number " << i << " From " << teamString << " Got Hit" << endl;
					}
					bulletHitEnemy = true;
					isMoving = false;

				}

			}
		}
		//if any soldier didn't took hit, the bullet can reach a wall or cover 
		if (maze[(int)y][(int)x] == WALL || maze[(int)y][(int)x] == COVER)
			isMoving = false;
	}

}


void Bullet::setDirection(double x, double y, double angle)
{
	this->x = x;
	this->y = y;
	this->direction_angle = angle;
}

void Bullet::SimulateMotion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage)
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * BULLET_SPEED;
		y += dy * BULLET_SPEED;

		security_map[(int)y][(int)x] += damage; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}

}

void Bullet::SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	double dx, dy;
	dx = cos(direction_angle);
	dy = sin(direction_angle);
	while (isMoving)
	{
		x += dx * BULLET_SPEED;
		y += dy * BULLET_SPEED;

		visibility_map[(int)y][(int)x] = 1; // drawing in map

		if (maze[(int)y][(int)x] == WALL)
			isMoving = false;
	}

}


