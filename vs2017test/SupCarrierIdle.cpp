#include "SupCarrierIdle.h"
#include "SupplyCarrier.h"
#include "SupCarrierGoToMedical.h"
#include "SupCarrierGoToArmory.h"
#include "SupCarrierFindPathToTarget.h"
#include "Soldier.h"
#include "SupCarrierWalking.h"
SupCarrierIdle::SupCarrierIdle()
{
}

SupCarrierIdle::~SupCarrierIdle()
{

}

void SupCarrierIdle::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	if (sc->getHP() <= 0.2*MAX_HP || sc->getMedicineStock() <= 0.2*MAX_MEDICINE_STOCK) {
		Medical* m = sc->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
		sc->setCurrentState(new SupCarrierGoToMedical(m->getX(), m->getY()));
	}
	else if (sc->getAmmo() <= 0.2*MAX_AMMO || sc->getGranades()<=0.1*MAX_GRANADES) {
		Armory *a = sc->getArmories().at(rand() % NUM_ARMORIES);
		sc->setCurrentState(new SupCarrierGoToArmory(a->getX(), a->getY()));
	}
	// if sup carrier is near a teamate and need to assist him
	// else state of searching for teammates to assist them.
	else {
		bool assistance = false;

		for (int i = 1; i < NUM_PLAYERS; i++)
		{
			Soldier *s = (Soldier*)sc->getTeam()[i];
			
			if (s!=nullptr && s->getNeedSupply() && s->getIsInCover()) {
				sc->setCurrentState(new SupCarrierFindPathToTarget(s->getCol(), s->getRow(), s));
				assistance = true;
				break;
			}

		}
		//if no one needs help, just walk between room till someone call for help
		if(!assistance)
			sc->setCurrentState(new SupCarrierWalking());

	}
	
	sc->getCurrentState()->OnEnter(sc);


}

void SupCarrierIdle::OnEnter(NPC * pn)
{
	pn->setIsIdle(true);

}

void SupCarrierIdle::OnExit(NPC * pn)
{
	pn->setIsIdle(false);

}
