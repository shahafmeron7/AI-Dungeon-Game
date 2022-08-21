#include "Grenade.h"
#include <math.h>



Grenade::Grenade()
{
}

Grenade::Grenade(double x, double y)
{
	double teta = 2 * 3.14 / NUM_BULLETS;
	this->x = x;
	this->y = y;
	for (int i = 0; i < NUM_BULLETS; i++)
		bullets[i] = new Bullet(x, y, i*teta);

}


Grenade::~Grenade()
{
}

bool Grenade::getIsExploded()
{
	for (int i = 0; i < NUM_BULLETS; i++)
		if (bullets[i]->getIsMoving()) {
			isExploded = false;
			return isExploded;
		}
	isExploded = true;
	return true;
}

void Grenade::Explode()
{
	isExploded = false;
	for (int i = 0; i < NUM_BULLETS; i++)
		bullets[i]->Fire();
}

void Grenade::Exploding(int maze[MSZ][MSZ], int targetColor, vector<NPC*> &team, vector<NPC*> &enemyTeam)
{
	//if not all bullets reached obstacle
	if (!isExploded)
		for (int i = 0; i < NUM_BULLETS; i++)
			bullets[i]->Move(maze,targetColor, team,enemyTeam);
}

void Grenade::show()
{
	for (int i = 0; i < NUM_BULLETS; i++)
		bullets[i]->show();

}

void Grenade::SimulateExplosion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage)
{
	int i;

	for (i = 0; i < NUM_BULLETS; i++)
		bullets[i]->Fire();

	for (i= 0; i < NUM_BULLETS; i++)
		bullets[i]->SimulateMotion(maze, security_map, damage);

}

void Grenade::SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ])
{
	int i;

	for (i = 0; i < NUM_BULLETS; i++)
		bullets[i]->Fire();

	for (i = 0; i < NUM_BULLETS; i++)
		bullets[i]->SimulateVisibility(maze, visibility_map);

}
