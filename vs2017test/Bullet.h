#pragma once
const double BULLET_SPEED = 0.1;
#include "NPC.h"
class Bullet
{

private:
	double x, y;
	double direction_angle;
	bool isMoving;
	bool bulletHitEnemy;
public:
	Bullet();
	Bullet(double x, double y, double angle);
	void show();
	~Bullet();
	int getRow() { return (int)y; }
	int getCol() { return (int)x; }
	void Fire() { isMoving = true; }
	void Move(int maze[MSZ][MSZ], int targetColor, vector<NPC*> &team, vector<NPC*> &enemyTeam);
	void setDirection(double x, double y, double angle);
	bool getIsMoving() { return isMoving; }
	bool getIsBulletHitEnemy() { return bulletHitEnemy; }

	void SimulateMotion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage);
	void SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);


};

