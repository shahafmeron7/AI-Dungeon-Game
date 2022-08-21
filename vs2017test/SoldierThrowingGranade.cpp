#include "SoldierThrowingGranade.h"
#include "Soldier.h"
#include "SoldierGoToCover.h"
#include "Idle.h"
SoldierThrowingGranade::SoldierThrowingGranade()
{
}

SoldierThrowingGranade::~SoldierThrowingGranade()
{
}

void SoldierThrowingGranade::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//after Throwing Granade going for cover, the soldier calling for help
	if (s->getSupplyCarrier() != nullptr && (s->getHP() <= 0.2*MAX_HP || s->getAmmo() <= 0.2*MAX_AMMO || s->getGranades() <= 0.5*MAX_GRANADES)) {
		s->setCurrentState(new SoldierGoToCover());
	}
	else {
		s->setCurrentState(new Idle());
	}
	s->getCurrentState()->OnEnter(s);

}

void SoldierThrowingGranade::OnEnter(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setIsThrowingGranade(true);
}

void SoldierThrowingGranade::OnExit(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setIsThrowingGranade(false);
}
