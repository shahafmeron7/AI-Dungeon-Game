#pragma once
#include "State.h"
#include "Soldier.h"

class SupCarrierProvideGranades :
	public State
{
private:
	Soldier* s;
public:
	SupCarrierProvideGranades(Soldier* s);
	~SupCarrierProvideGranades();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

