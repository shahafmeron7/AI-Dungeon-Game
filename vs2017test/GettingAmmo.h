#pragma once
#include "State.h"
class GettingAmmo :
	public State
{
public:
	GettingAmmo();
	~GettingAmmo();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

