#pragma once
#include "State.h"
class SoldierIsShooting :
	public State
{
public:
	SoldierIsShooting();
	~SoldierIsShooting();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

