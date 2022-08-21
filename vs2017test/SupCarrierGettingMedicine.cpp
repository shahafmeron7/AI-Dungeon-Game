#include "SupCarrierGettingMedicine.h"
#include "SupCarrierGoToArmory.h"
#include "SupplyCarrier.h"
#include "SupCarrierIdle.h"
#include "SupCarrierGettingMedicineStock.h"
SupCarrierGettingMedicine::SupCarrierGettingMedicine() {

}
SupCarrierGettingMedicine::~SupCarrierGettingMedicine() { }


void SupCarrierGettingMedicine::Transform(NPC* pn) {
	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	//if he has low stock of medicine
	if (sc->getMedicineStock() <= 0.2*MAX_MEDICINE_STOCK) {
		sc->setCurrentState(new SupCarrierGettingMedicineStock());
	}
	//need to check if needs to return to previous state.
	else if (sc->getInterruptedState()) {
		sc->setCurrentState(sc->getInterruptedState());
	}
	//if he has low stock of ammo
	else if(sc->getAmmo() <= 0.2*MAX_AMMO || sc->getGranades() <= 0.5*MAX_GRANADES) {
		Armory *a = sc->getArmories().at(rand() % NUM_ARMORIES);
		sc->setCurrentState(new SupCarrierGoToArmory(a->getX(), a->getY()));
	}
	else {
		sc->setCurrentState(new SupCarrierIdle());

	}
	// else need to add state of searching for teammates to assist them.
	sc->getCurrentState()->OnEnter(sc);


}
void SupCarrierGettingMedicine::OnEnter(NPC* pn) {
	pn->setIsGettingMedicine(true);
}
void SupCarrierGettingMedicine::OnExit(NPC* pn) {
	pn->setIsGettingMedicine(false);

}