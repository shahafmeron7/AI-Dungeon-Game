#include "SoldierIsShooting.h"
#include "Soldier.h"
#include "SoldierGoToCover.h"
#include "SoldierThrowingGranade.h"
#include "Idle.h"
#include "SoldierSearchingTarget.h"
SoldierIsShooting::SoldierIsShooting()
{
}

SoldierIsShooting::~SoldierIsShooting()
{
}

void SoldierIsShooting::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//if I have low hp, I will throw grenades if I still have some before going to cover + add some rand to give it more realistic
	if(s->getHP() <= 0.2*MAX_HP && s->getGranades()>0 && rand()%2 == 1){
		s->setCurrentState(new SoldierThrowingGranade());

	}
	//if soldier in combat and have low health or low ammo, need to go for cover
	else if (s->getHP() <= 0.2*MAX_HP || (s->getAmmo() <= 0.1*MAX_AMMO && s->getGranades() < 0.5*MAX_GRANADES)) {
		s->setCurrentState(new SoldierGoToCover());
	}

	//if soldier in pass need to go other room and start searching for enemy
	else if (s->getIsInPass()) {
		s->setCurrentState(new SoldierSearchingTarget());
	}
	else {
		s->setCurrentState(new Idle());

	}
	s->getCurrentState()->OnEnter(s);
}

void SoldierIsShooting::OnEnter(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setIsShooting(true);
}

void SoldierIsShooting::OnExit(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setIsShooting(false);
}
