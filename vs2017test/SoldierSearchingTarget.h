#pragma once
#include "State.h"
class SoldierSearchingTarget :
	public State
{
public:
	SoldierSearchingTarget();
	~SoldierSearchingTarget();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

