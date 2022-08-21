#pragma once
#include "State.h"
class GettingGranades :
	public State
{
public:
	GettingGranades();
	~GettingGranades();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);

};

