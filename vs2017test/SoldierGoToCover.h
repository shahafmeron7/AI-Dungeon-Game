#pragma once
#include "State.h"
class SoldierGoToCover :
	public State
{
public:
	SoldierGoToCover();
	~SoldierGoToCover();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

