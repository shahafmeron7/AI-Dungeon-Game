#include "SupCarrierProvideAmmo.h"
#include "SupplyCarrier.h"
#include "SupCarrierIdle.h"
#include"SupCarrierProvideMedicine.h"
#include "SupCarrierProvideGranades.h"


SupCarrierProvideAmmo::SupCarrierProvideAmmo(Soldier* s)
{
	this->s = s;
}

SupCarrierProvideAmmo::~SupCarrierProvideAmmo()
{
}

void SupCarrierProvideAmmo::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);

	//if (s->getHP() <= 0.2*MAX_HP || s->getGranades() <= 0.5*MAX_GRANADES) {
	//	//going back to provide medicine/grenades
	//	sc->setCurrentState(sc->getInterruptedState());

	//}
	//else {
	//	sc->setCurrentState(new SupCarrierIdle());
	//}
	sc->setCurrentState(new SupCarrierIdle());

	sc->getCurrentState()->OnEnter(sc);

}

void SupCarrierProvideAmmo::OnEnter(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingAmmo(true);
	sc->setIsMoving(false);
}

void SupCarrierProvideAmmo::OnExit(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingAmmo(false);

}
