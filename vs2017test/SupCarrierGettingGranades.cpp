#include "SupCarrierGettingGranades.h"
#include "SupplyCarrier.h"
#include "SupCarrierGoToMedical.h"
#include "SupCarrierIdle.h"

SupCarrierGettingGranades::SupCarrierGettingGranades()
{
}

SupCarrierGettingGranades::~SupCarrierGettingGranades()
{
}

void SupCarrierGettingGranades::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	// Interrupted state, in case he got shot, need to fill HP.

	if (sc->getHP() <= 0.2*MAX_HP) {
		sc->setInterruptedState(this);
		Medical* m = sc->getMedicals().at(rand() % NUM_MEDICAL_CENTERS);
		sc->setCurrentState(new SupCarrierGoToMedical(m->getX(), m->getY()));
	}
	else {
		// else need to add state of searching for teammates to assist them.
		sc->setCurrentState(new SupCarrierIdle());
	}
	sc->getCurrentState()->OnEnter(sc);
}

void SupCarrierGettingGranades::OnEnter(NPC * pn)
{
	pn->setIsGettingGranades(true);

}

void SupCarrierGettingGranades::OnExit(NPC * pn)
{
	pn->setIsGettingGranades(false);


}
