#pragma once
#include "State.h"
#include "Soldier.h"
class SupCarrierProvideMedicine :
	public State
{
private: 
	Soldier* s;
public:
	SupCarrierProvideMedicine(Soldier* s);
	~SupCarrierProvideMedicine();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

