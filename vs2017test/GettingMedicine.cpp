#include "GettingMedicine.h"
#include "GoToArmory.h"
#include "Soldier.h"
#include "Idle.h"
#include "SoldierGoToCover.h"

GettingMedicine::GettingMedicine()
{
}

GettingMedicine::~GettingMedicine()
{
}

void GettingMedicine::Transform(NPC * pn)
{
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	if (s->getIsShooting()) {
		s->setCurrentState(new SoldierGoToCover());

	}
	//if my SC is dead, the soldier needs to Go to armory in case soldier have low ammo
	if (s->getSupplyCarrier()==nullptr) {
		if (s->getAmmo() <= 0.2*MAX_AMMO || s->getGranades()<=0.5*MAX_GRANADES)
		{
			Armory *a = s->getArmories().at(rand() % NUM_ARMORIES);
			s->setCurrentState(new GoToArmory(a->getX(), a->getY()));
			s->getCurrentState()->OnEnter(s);

		}
		if (s->getHP() <= MAX_HP) {
			Medical *m = s->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
			s->setCurrentState(new GoToArmory(m->getX(), m->getY()));
			s->getCurrentState()->OnEnter(s);

		}
	}
	else {
		//if im here it means im getting medicine from supply carrier
		if (s->getInterruptedState()) {
			s->setCurrentState(s->getInterruptedState());
		}
		//else im in medical center , going back idle
		else {
			s->setCurrentState(new Idle());
		}
	}
	s->getCurrentState()->OnEnter(s);
}

void GettingMedicine::OnEnter(NPC * pn)
{
	pn->setIsGettingMedicine(true);

}

void GettingMedicine::OnExit(NPC * pn)
{
	pn->setIsGettingMedicine(false);

}
