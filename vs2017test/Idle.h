#pragma once
#include "State.h"
class Idle :
	public State
{
public:
	Idle();
	~Idle();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

