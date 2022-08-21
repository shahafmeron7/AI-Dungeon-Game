#pragma once
#include "State.h"
class SupCarrierGoToMedical :
	public State
{
private:
	int x, y;

public:
	SupCarrierGoToMedical(int x, int y);
	~SupCarrierGoToMedical();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

