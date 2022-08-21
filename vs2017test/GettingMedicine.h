#pragma once
#include "State.h"
class GettingMedicine:
	public State
{
public:
	GettingMedicine();
	~GettingMedicine();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);


};

