#pragma once
#include "NPC.h"
#include "SupplyCarrier.h"
#include "Grenade.h"

using namespace std;

class Soldier:
	public NPC
{
protected:
	double ammo, granades;
	bool needAmmo, needMedicine, needSupply, isShooting, startShooting;
	bool isThrowingGranade,startThrowing,inCover,inPass;
	int count_bullet_not_hit_target = 0;
	SupplyCarrier* sc;
	Bullet* bullet;
	Grenade* grenade;

public:
	Soldier(int x, int y, Room rooms[NUM_ROOMS], vector <Medical*> medicals, vector <Armory*> armories, SupplyCarrier* sc);
	Soldier();
	~Soldier();


	void DoSomeThing(int maze[MSZ][MSZ]); // kind of MAIN function
	SupplyCarrier* getSupplyCarrier() { return sc; };
	void setSupplyCarrier(SupplyCarrier* sc) { this->sc = sc; }
	double getAmmo() { return ammo; }
	double getGranades() { return granades; }
	bool checkIfSupCarrierHere();
	bool getIsInCover() { return inCover; }
	bool getIsInPass() { return inPass; }
	void setNeedSupply(bool value) { needSupply = value; }
	void setIsShooting(bool value) { isShooting = value; }
	void setIsInPass(bool value) { inPass = value; }
	void setIsThrowingGranade(bool value) { isThrowingGranade = value; }
	bool getNeedSupply() { return needSupply; }
	bool getNeedAmmo() { return needAmmo; }
	bool getNeedMedicine() { return needMedicine; };
	void DrawMe(int team);
	bool getIsShooting() { return isShooting; }
	bool getIsThrowingGranade() { return isThrowingGranade; }
	void setBulletDidntHitCount() { count_bullet_not_hit_target++; }
	bool getBulletDidntHitCount() { return count_bullet_not_hit_target; }
	void soldierShooting(int maze[MSZ][MSZ]);
	void soldierThrowing(int maze[MSZ][MSZ]);
	void setBullet(Bullet* b) { bullet = b; }
	void setGrenade(Grenade* g) { grenade = g; }
	void setIsInCover(bool value) { inCover = value; }

	Bullet* getBullet() { return bullet; }
	Grenade* getGrenade() { return grenade; }


};

