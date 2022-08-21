#include "SupCarrierProvideGranades.h"
#include "SupplyCarrier.h"
#include "SupCarrierProvideMedicine.h"
#include "SupCarrierIdle.h"
#include "SupCarrierProvideAmmo.h"

SupCarrierProvideGranades::SupCarrierProvideGranades(Soldier* s)
{
	this->s = s;
}

SupCarrierProvideGranades::~SupCarrierProvideGranades()
{
}

void SupCarrierProvideGranades::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	//if the soldier need medicine
	/*if (s->getHP() <= 0.2*MAX_HP || s->getAmmo() <= 0.2*MAX_AMMO) {
		sc->setCurrentState(sc->getInterruptedState());
	}
	else {
		sc->setCurrentState(new SupCarrierIdle());
	}*/
	sc->setCurrentState(new SupCarrierIdle());

	sc->getCurrentState()->OnEnter(sc);
}

void SupCarrierProvideGranades::OnEnter(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingGranades(true);
	sc->setIsMoving(false);

}

void SupCarrierProvideGranades::OnExit(NPC * pn)
{

	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingGranades(false);
}
