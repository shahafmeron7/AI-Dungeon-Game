#include "SoldierLookingForEnemey.h"
#include "Soldier.h"
#include "SoldierThrowingGranade.h"
#include "SoldierIsShooting.h"
#include "Idle.h"

SoldierLookingForEnemey::SoldierLookingForEnemey()
{
}

SoldierLookingForEnemey::~SoldierLookingForEnemey()
{
}

void SoldierLookingForEnemey::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//start shooting on enemy if I nearby
	if (s->checkIfTargetIsNearby(ENEMY) && (s->getAmmo()>=0.5*MAX_AMMO || s->getGranades()>=0.4*MAX_GRANADES)) {
		int chance = rand() % 30;
		//some realistic desicion to throw grenades / shot bullet
		if (chance > 15) {
			s->setCurrentState(new SoldierThrowingGranade());

		}
		else {
			s->setCurrentState(new SoldierIsShooting());

		}
	}
	//if no enemy nearby going idle
	else {
		s->setCurrentState(new Idle());

	}

	s->getCurrentState()->OnEnter(s);

}

void SoldierLookingForEnemey::OnEnter(NPC * pn)
{
	pn->setIsSearchingEnemyInRoom(true);
	pn->setIsMoving(true);
}

void SoldierLookingForEnemey::OnExit(NPC * pn)
{
	pn->setIsSearchingEnemyInRoom(false);
	pn->setIsMoving(false);
}
