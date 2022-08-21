#pragma once
#include "Definitions.h"
#include "State.h"
#include "Medical.h"
#include <vector>
#include "Armory.h"
#include <iostream>
#include "Cell.h"
#include <queue>
#include "CompareCells.h"
#include <limits.h>
#include "Room.h"


using namespace std;

const int MAX_AMMO = 50;
const int MIN_AMMO = 0;
const int MAX_GRANADES = 2;
const int MIN_GRANADES = 0;

const int MAX_HP = 500;
const double SPEED = 0.06;
const double SPEED_SOLDIER = 0.1;

class State;
class NPC
{

private:

protected:
	double x, y;
	double targetX, targetY;
	double hp;
	bool isMoving, isIdle, searching,goingToCover, searchingEnemyInRoom;
	bool isGettingMedicine, isGettingGranades, isGettingAmmo;
	int index_target;
	vector <Medical*> medicals;
	vector <Armory*> armories;
	vector <NPC*> team;
	vector <NPC*> enemyTeam;
	vector <Cell*> path;
	Room rooms[NUM_ROOMS];
	State* pCurrentState;
	State* pInterruptedState;
public:
	int pType;
	NPC(int x, int y,Room rooms[NUM_ROOMS] ,vector <Medical*> medicals, vector <Armory*> armories);
	NPC();
	~NPC();
	void DoSomeThing(int maze[MSZ][MSZ]); // kind of MAIN function

	void setIsMoving(bool value) { isMoving = value; }
	void setGoingToCover(bool value) { goingToCover = value; }
	

	void setIsGettingAmmo(bool value) { isGettingAmmo = value; }
	void setIsGettingMedicine(bool value) { isGettingMedicine = value; }
	void setIsGettingGranades(bool value) { isGettingGranades = value; }
	void setIsSearchingEnemyInRoom(bool value) { searchingEnemyInRoom = value; }

	void setIsIdle(bool value) { isIdle = value; }
	void setIsSearching(bool value) { searching = value; }
	void setCurrentState(State* ps) { pCurrentState = ps; }
	void setTeam(vector <NPC*> team) { this->team = team; }
	void setEnemyTeam(vector <NPC*>& team) { this->enemyTeam = team; }
	void setTargetEnemy();
	vector <Medical*> getMedicals() { return medicals; }
	vector <Armory*> getArmories() { return armories; }
	vector <NPC*> getTeam() { return team; }

	Room* getRooms() { return rooms; }

	State* getCurrentState() { return pCurrentState; }
	double getHP() { return hp; }
	void setHP(int val) { hp = val; }
	void setInterruptedState(State* ps) { pInterruptedState = ps; }
	State* getInterruptedState() { return pInterruptedState; }
	double getTargetX() { return targetX; }
	double getTargetY() { return targetY; }
	double getRow() { return y; }
	double getCol() { return x; }

	void AstarSearch(int maze[MSZ][MSZ],int xTarget, int yTarget);
	void CheckNeighbor(int maze[MSZ][MSZ],int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq,
		vector <Cell> &grays, vector <Cell>&blacks);
	bool BFSIteration(int maze[MSZ][MSZ]);
	bool CheckNeighborBFS(int maze[MSZ][MSZ], Cell * pCurrent, vector<Cell>& grays, vector<Cell>& blacks, int row, int col);
	void setDestination(double destX, double destY);
	bool checkIfTargetIsNearby(int targetObject);
	void RestorePath(Cell* ps);
	bool gotHit();

	void DrawMe(int team);

	
};

