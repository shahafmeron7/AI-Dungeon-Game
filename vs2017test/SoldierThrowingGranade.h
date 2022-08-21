#pragma once
#include "State.h"
class SoldierThrowingGranade :
	public State
{
public:
	SoldierThrowingGranade();
	~SoldierThrowingGranade();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

