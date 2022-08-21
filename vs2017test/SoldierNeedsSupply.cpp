#include "SoldierNeedsSupply.h"
#include "Soldier.h"
#include "GettingAmmo.h"
#include "GettingMedicine.h"
#include "GettingGranades.h"
#include "Idle.h"
SoldierNeedsSupply::SoldierNeedsSupply()
{
}

SoldierNeedsSupply::~SoldierNeedsSupply()
{
}

void SoldierNeedsSupply::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	

	if (s->getHP() <= 0.2*MAX_HP) {
		//s->setInterruptedState(this);
		s->setCurrentState(new GettingMedicine());
	}
	//if the soldier need ammo
	else if (s->getAmmo() <= 0.2*MAX_AMMO) {
		//s->setInterruptedState(this);
		s->setCurrentState(new GettingAmmo());

	}
	//if the soldier need granades
	else if (s->getGranades() <= 0.5*MAX_GRANADES) {
		//s->setInterruptedState(this);
		s->setCurrentState(new GettingGranades());

	}
	else {
		s->setCurrentState(new Idle());

	}
	s->getCurrentState()->OnEnter(s);


}

void SoldierNeedsSupply::OnEnter(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	s->setNeedSupply(true);

}

void SoldierNeedsSupply::OnExit(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	//after this will changed to false, the soldier will get in condition "gettingAmmo/Medicine"  on DoSomething 
	s->setNeedSupply(false);
}
