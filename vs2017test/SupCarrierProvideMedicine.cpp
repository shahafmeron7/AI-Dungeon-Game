#include "SupCarrierProvideMedicine.h"
#include "SupplyCarrier.h"
#include "SupCarrierProvideAmmo.h"
#include "SupCarrierIdle.h"
#include "SupCarrierProvideGranades.h"


SupCarrierProvideMedicine::SupCarrierProvideMedicine(Soldier* s)
{
	this->s = s;
}

SupCarrierProvideMedicine::~SupCarrierProvideMedicine()
{
}

void SupCarrierProvideMedicine::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	//after getting medicine need to go back to my last state. in this case, it will be supplycarrierIdle.
	
	//if the soldier need ammo
	//if (s->getAmmo() <= 0.2*MAX_AMMO || s->getGranades() <= 0.5*MAX_GRANADES) {

	//	//going back to provide ammo/grenades
	//	sc->setCurrentState(sc->getInterruptedState());

	//}
	//else {
	//	sc->setCurrentState(new SupCarrierIdle());
	//}
	
	sc->setCurrentState(new SupCarrierIdle());

	sc->getCurrentState()->OnEnter(sc);

}

void SupCarrierProvideMedicine::OnEnter(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingMedicine(true);
	sc->setIsMoving(false);
	

}

void SupCarrierProvideMedicine::OnExit(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	sc->setProvidingMedicine(false);



}
