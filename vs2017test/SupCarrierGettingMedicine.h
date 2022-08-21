#pragma once
#include "State.h"
class SupCarrierGettingMedicine :
	public State
{
public:
	SupCarrierGettingMedicine();
	~SupCarrierGettingMedicine();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

