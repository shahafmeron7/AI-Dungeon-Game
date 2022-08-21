#pragma once
#include "State.h"
#include "glut.h"

class GoToMedical:
	public State
{
private:
	int x, y;
public:
	GoToMedical(int x,int y);
	~GoToMedical();
	
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);
};

