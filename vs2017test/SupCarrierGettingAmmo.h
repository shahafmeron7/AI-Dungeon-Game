#pragma once
#include "State.h"
class SupCarrierGettingAmmo :
	public State
{
public:
	SupCarrierGettingAmmo();
	~SupCarrierGettingAmmo();
	void Transform(NPC * pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

