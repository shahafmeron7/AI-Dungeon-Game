#include "SupCarrierFindPathToTarget.h"
#include "SupCarrierProvideAmmo.h"
#include"SupCarrierProvideMedicine.h"
#include "SupplyCarrier.h"
#include "SupCarrierProvideGranades.h"
#include "SupCarrierIdle.h"
SupCarrierFindPathToTarget::SupCarrierFindPathToTarget(int x, int y, Soldier* s)
{
	this->x = x;
	this->y = y;
	this->s = s;
	
}

SupCarrierFindPathToTarget::~SupCarrierFindPathToTarget()
{
}

void SupCarrierFindPathToTarget::Transform(NPC * pn)
{
	
	
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);

	//if the soldier need medicine
	if(s->getHP() <= 0.2*MAX_HP){
		//sc->setInterruptedState(this);
		sc->setCurrentState(new SupCarrierProvideMedicine(s));
	}
	//if the soldier need ammo
	else if( s->getAmmo() <= 0.2*MAX_AMMO){
		//sc->setInterruptedState(this);
		sc->setCurrentState(new SupCarrierProvideAmmo(s));
	}
	//if the soldier need granades
	else if(s->getGranades() <= 0.5*MAX_GRANADES){
		//sc->setInterruptedState(this);
		sc->setCurrentState(new SupCarrierProvideGranades(s));

	}
	else {
		sc->setCurrentState(new SupCarrierIdle());

	}
	sc->getCurrentState()->OnEnter(sc);

}

void SupCarrierFindPathToTarget::OnEnter(NPC * pn)
{
	pn->setIsSearching(true);
	pn->setIsMoving(true);
	//sup carrier need to reach his destination, this Set Function is for Soldier to wait for him.
	pn->setDestination(x, y);
	s->setNeedSupply(true);
	
}

void SupCarrierFindPathToTarget::OnExit(NPC * pn)
{
	pn->setIsSearching(false);
	pn->setIsMoving(false);
	s->setNeedSupply(false);

	//sup carrier  reached his destination, this Set Function is for supply carrier to provide him suppliments.



}
