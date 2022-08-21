#include "SoldierSearchingTarget.h"
#include "Soldier.h"
#include "SoldierIsShooting.h"
#include "SoldierLookingForEnemey.h"
#include "Idle.h"
#include "SoldierThrowingGranade.h"

SoldierSearchingTarget::SoldierSearchingTarget()
{
}

SoldierSearchingTarget::~SoldierSearchingTarget()
{
}

void SoldierSearchingTarget::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//if soldier have enough supplies start shooting

	//if soldier see enemy soldier in the middle of the way, engage.
	if (s->getIsThrowingGranade()) {
		s->setCurrentState(new SoldierThrowingGranade());

	}
	else if (s->getIsShooting()) {
		s->setCurrentState(new SoldierIsShooting());

	}
	else if (s->getHP() >= 0.6*MAX_HP &&
		(s->getAmmo() >= 0.6*MAX_AMMO || s->getGranades() >= 0.4*MAX_GRANADES)
		)
	{
		s->setCurrentState(new SoldierLookingForEnemey());

	}
	//else checking what I need to do, going back Idle
	else {
		s->setCurrentState(new Idle());

	}


	s->getCurrentState()->OnEnter(s);

}

void SoldierSearchingTarget::OnEnter(NPC * pn)
{
	pn->setIsSearching(true);
	pn->setIsMoving(true);
	Room room = pn->getRooms()[rand()%NUM_ROOMS];
	int xr = room.getCenterX();
	int yr = room.getCenterY();
	int wr = room.getWidth();
	int hr = room.getHeight();
	int new_x = xr - wr / 2 + rand() % wr;
	int new_y = yr - hr / 2 + rand() % hr;
	//initial random position inside the room bounderis. 
	//setting random room to search there for potential enemy soldier
	pn->setDestination(new_x, new_y);
}

void SoldierSearchingTarget::OnExit(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	pn->setIsSearching(false);
	pn->setIsMoving(false);
	s->setIsInPass(false);
	
}
