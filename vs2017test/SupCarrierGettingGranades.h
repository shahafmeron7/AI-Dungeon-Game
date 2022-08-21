#pragma once
#include "State.h"
class SupCarrierGettingGranades :
	public State
{
public:
	SupCarrierGettingGranades();
	~SupCarrierGettingGranades();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

