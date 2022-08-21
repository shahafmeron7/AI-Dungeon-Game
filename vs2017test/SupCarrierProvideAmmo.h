#pragma once
#include "State.h"
#include "Soldier.h"
class SupCarrierProvideAmmo :
	public State
{

private:
	Soldier* s;
public:
	SupCarrierProvideAmmo(Soldier* s);
	~SupCarrierProvideAmmo();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

