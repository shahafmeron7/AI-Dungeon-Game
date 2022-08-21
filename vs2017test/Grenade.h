#pragma once
#include "Bullet.h"
const int NUM_BULLETS = 100;

class Grenade
{

private: 
	double x, y;
	Bullet* bullets[NUM_BULLETS];
	bool isExploded;
public:
	Grenade();
	Grenade(double x, double y);
	~Grenade();
	bool getIsExploded();
	void Explode();
	void Exploding(int maze[MSZ][MSZ], int targetColor, vector<NPC*> &team, vector<NPC*> &enemyTeam);
	void show();
	void SimulateExplosion(int maze[MSZ][MSZ], double security_map[MSZ][MSZ], double damage);
	void SimulateVisibility(int maze[MSZ][MSZ], double visibility_map[MSZ][MSZ]);
};

