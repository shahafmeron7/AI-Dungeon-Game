#pragma once
#include "State.h"
class SupCarrierWalking :
	public State
{
public:
	SupCarrierWalking();
	~SupCarrierWalking();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

