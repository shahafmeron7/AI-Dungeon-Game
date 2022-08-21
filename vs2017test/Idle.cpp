#include "Idle.h"
#include "Soldier.h"
#include "GoToMedical.h"
#include "GoToArmory.h"
#include "SoldierNeedsSupply.h"
#include "SoldierGoToCover.h"
#include "SoldierSearchingTarget.h"
Idle::Idle()
{
}

Idle::~Idle()
{
}

void Idle::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	//if my SupplyCarrier died, the I need to go to medical.
	if (s->getSupplyCarrier()==nullptr && s->getHP() <= 0.2*MAX_HP) {
		Medical* m = s->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
		s->setCurrentState(new GoToMedical(m->getX(), m->getY()));
	}
	//if my SupplyCarrier died, the I need to go to armory.

	else if (s->getSupplyCarrier() == nullptr && (s->getAmmo() <= 0.2*MAX_AMMO|| s->getAmmo() <= 0.5*MAX_GRANADES))
	{
		Armory *a = s->getArmories().at(rand() % NUM_ARMORIES);
		s->setCurrentState(new GoToArmory(a->getX(), a->getY()));
	}
	//need to call SupplyCarrier if he is not dead and take cover
	else if (s->getSupplyCarrier() != nullptr && (s->getHP()<=0.2*MAX_HP || s->getAmmo() <= 0.2*MAX_AMMO || s->getGranades() <= 0.5*MAX_GRANADES)) {
		s->setCurrentState(new SoldierGoToCover());
	}
	//
	// else need to add state of searching for teammates to assist them.
	else {
		s->setCurrentState(new SoldierSearchingTarget());
	}
	
	s->getCurrentState()->OnEnter(s);

}

void Idle::OnEnter(NPC * pn)
{
	pn->setIsIdle(true);

}

void Idle::OnExit(NPC * pn)
{
	pn->setIsIdle(false);

}
