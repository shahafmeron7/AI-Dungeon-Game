#include "SupCarrierWalking.h"
#include "SupplyCarrier.h"
#include "SupCarrierIdle.h"

SupCarrierWalking::SupCarrierWalking()
{
}

SupCarrierWalking::~SupCarrierWalking()
{
}

void SupCarrierWalking::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	sc->setCurrentState(new SupCarrierIdle());
	sc->getCurrentState()->OnEnter(sc);
}

void SupCarrierWalking::OnEnter(NPC * pn)
{
	pn->setIsSearching(true);
	pn->setIsMoving(true);
	Room room = pn->getRooms()[rand() % NUM_ROOMS];
	int xr = room.getCenterX();
	int yr = room.getCenterY();
	int wr = room.getWidth();
	int hr = room.getHeight();
	int new_x = xr - wr / 2 + rand() % wr;
	int new_y = yr - hr / 2 + rand() % hr;
	//initial random position inside the room bounderis. 
	//setting random room to search there for potential enemy soldier
	pn->setDestination(new_x, new_y);
}

void SupCarrierWalking::OnExit(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	pn->setIsSearching(false);
	pn->setIsMoving(false);

}
