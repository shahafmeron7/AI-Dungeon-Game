#include "SupCarrierGettingMedicineStock.h"
#include "GoToArmory.h"
#include "SupCarrierGettingMedicine.h"
#include "SupCarrierGoToArmory.h"
#include "SupCarrierIdle.h"

SupCarrierGettingMedicineStock::SupCarrierGettingMedicineStock()
{
}

SupCarrierGettingMedicineStock::~SupCarrierGettingMedicineStock()
{
}


void SupCarrierGettingMedicineStock::Transform(NPC * pn)
{
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	if (sc->getHP() <= 0.2*MAX_HP) {
		sc->setCurrentState(new SupCarrierGettingMedicine());
	}
	else if (sc->getAmmo() <= 0.2*MAX_AMMO) {
		Armory *a = sc->getArmories().at(rand() % NUM_ARMORIES);
		sc->setCurrentState(new SupCarrierGoToArmory(a->getX(), a->getY()));
	}
	//if the supply carrier has full hp, full medicine stock and full ammo, need to go back to Idle.
	else {
		sc->setCurrentState(new SupCarrierIdle());

	}
	
	sc->getCurrentState()->OnEnter(sc);

}

void SupCarrierGettingMedicineStock::OnEnter(NPC * pn)
{
	((SupplyCarrier*)pn)->setIsGettingMedicinceStock(true);

}

void SupCarrierGettingMedicineStock::OnExit(NPC * pn)
{
	((SupplyCarrier*)pn)->setIsGettingMedicinceStock(false);

}
