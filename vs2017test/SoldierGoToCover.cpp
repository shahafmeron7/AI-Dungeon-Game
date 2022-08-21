#include "SoldierGoToCover.h"
#include "SoldierNeedsSupply.h"
#include "Soldier.h"
SoldierGoToCover::SoldierGoToCover()
{
}

SoldierGoToCover::~SoldierGoToCover()
{
}

void SoldierGoToCover::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//after going for cover the soldier calling for help
	s->setCurrentState(new SoldierNeedsSupply());
	s->getCurrentState()->OnEnter(s);

}

void SoldierGoToCover::OnEnter(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	pn->setGoingToCover(true);
	pn->setIsMoving(true);
	s->setIsInCover(false);

}

void SoldierGoToCover::OnExit(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setIsInCover(true);
	pn->setGoingToCover(false);

	pn->setIsMoving(false);
}
