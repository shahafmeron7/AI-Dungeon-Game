#pragma once
#include "State.h"
#include "Soldier.h"
class SupCarrierFindPathToTarget :
	public State
{
private:
	int x, y;
	Soldier* s;
public:
	SupCarrierFindPathToTarget(int x,int y,Soldier* s);
	~SupCarrierFindPathToTarget();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

