#pragma once
#include "State.h"
class SoldierNeedsSupply :
	public State
{
public:
	SoldierNeedsSupply();
	~SoldierNeedsSupply();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

