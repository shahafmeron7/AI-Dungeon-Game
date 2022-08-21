#pragma once
#include "GoToArmory.h"
#include "GettingAmmo.h"
#include "Soldier.h"
#include "GettingGranades.h"
#include "Idle.h"
GoToArmory::GoToArmory(int x, int y)
{
	this->x = x;
	this->y = y;

}

GoToArmory::~GoToArmory() {}


void GoToArmory::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;

	OnExit(s);
	if (s->getAmmo() <= 0.2*MAX_AMMO) {
		s->setCurrentState(new GettingAmmo());
	}
	if(s->getGranades() <= 0.5*MAX_GRANADES){
		s->setCurrentState(new GettingGranades());
	}
	//if soldier at the armory and he needs to get back to his prev state. Idle/need medicine/chasing enemy
	else {
		s->setCurrentState(new Idle());
	}
	s->getCurrentState()->OnEnter(s);

}

void GoToArmory::OnEnter(NPC * pn)
{
	pn->setIsMoving(true);
	pn->setIsSearching(true);
	pn->setDestination(x, y);

}

void GoToArmory::OnExit(NPC * pn)
{
	pn->setIsMoving(false);
	pn->setIsSearching(false);

}


