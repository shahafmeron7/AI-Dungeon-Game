#pragma once
#include "State.h"
class SupCarrierIdle :
	public State
{

public:
	SupCarrierIdle();
	~SupCarrierIdle();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

