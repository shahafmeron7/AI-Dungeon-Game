#pragma once
#include "State.h"
class SoldierLookingForEnemey :
	public State
{
public:
	SoldierLookingForEnemey();
	~SoldierLookingForEnemey();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

