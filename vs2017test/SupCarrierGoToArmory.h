#pragma once
#include "Definitions.h"
#include "State.h"
#include "glut.h"


class SupCarrierGoToArmory :
	public State

{
private:
	int x, y;
public:
	SupCarrierGoToArmory(int x, int y);
	~SupCarrierGoToArmory();
	void Transform(NPC * pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

