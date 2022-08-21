#include "SupCarrierGoToArmory.h"
#include "SupplyCarrier.h"
#include "SupCarrierGettingAmmo.h"
#include "SupCarrierGoToMedical.h"
#include "SupCarrierGettingGranades.h"

SupCarrierGoToArmory::SupCarrierGoToArmory(int x, int y) {
	this->x = x;
	this->y = y;
}
SupCarrierGoToArmory::~SupCarrierGoToArmory(){ }


void SupCarrierGoToArmory::Transform(NPC* pn){
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	// Interrupted state if hp is low, need to go to medical for medicine
	if (sc->getHP() <= 0.2*MAX_HP) {
		sc->setInterruptedState(this);
		Medical* m = sc->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
		sc->setCurrentState(new SupCarrierGoToMedical(m->getX(), m->getY()));
	}
	else if(sc->getAmmo()<=0.2*MAX_AMMO) {

		sc->setCurrentState(new SupCarrierGettingAmmo());
	}
	else if (sc->getGranades() <= 0.5*MAX_GRANADES) {
		sc->setCurrentState(new SupCarrierGettingGranades());

	}

	sc->getCurrentState()->OnEnter(sc);

}
void SupCarrierGoToArmory::OnEnter(NPC* pn){
	pn->setDestination(x, y);
	pn->setIsMoving(true);
	pn->setIsSearching(true);

}
void SupCarrierGoToArmory::OnExit(NPC* pn){
	pn->setIsMoving(false);
	pn->setIsSearching(false);


}
