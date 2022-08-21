#pragma once
#include "Definitions.h"
#include "State.h"
#include "glut.h"


class GoToArmory:
	public State

{
private:
	int x, y;
	
public:
	GoToArmory(int x, int y);
	~GoToArmory();

	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

