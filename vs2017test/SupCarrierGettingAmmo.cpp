#include "SupCarrierGettingAmmo.h"
#include "SupplyCarrier.h"
#include "SupCarrierGoToMedical.h"
#include "SupCarrierIdle.h"
#include "SupCarrierGettingGranades.h"

SupCarrierGettingAmmo::SupCarrierGettingAmmo() {

}
SupCarrierGettingAmmo::~SupCarrierGettingAmmo() { }


void SupCarrierGettingAmmo::Transform(NPC* pn) {
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);

	// Interrupted state, in case he got shot, need to fill HP.
	if (sc->getHP() <= 0.2*MAX_HP) {
		sc->setInterruptedState(this);
		Medical* m = sc->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
		sc->setCurrentState(new SupCarrierGoToMedical(m->getX(), m->getY()));
	}
	//sup carrier already at armory, need to check if need to fill granades stock
	else if (sc->getGranades() <= 0.1*MAX_GRANADES) {
		sc->setCurrentState(new SupCarrierGettingGranades());
	}
	else {
		// else need to add state of searching for teammates to assist them.
		sc->setCurrentState(new SupCarrierIdle());
	}
	sc->getCurrentState()->OnEnter(sc);

}
void SupCarrierGettingAmmo::OnEnter(NPC* pn) {
	pn->setIsGettingAmmo(true);
}
void SupCarrierGettingAmmo::OnExit(NPC* pn) {
	pn->setIsGettingAmmo(false);

}