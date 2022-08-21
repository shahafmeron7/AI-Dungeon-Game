
#include "SupCarrierGoToMedical.h"
#include "SupplyCarrier.h"
#include "SupCarrierGettingMedicineStock.h"
#include "SupCarrierGettingMedicine.h"
#include "SupCarrierGoToArmory.h"
#include "SupCarrierIdle.h"


SupCarrierGoToMedical::SupCarrierGoToMedical(int x, int y) {
	this->x = x;
	this->y = y;
}
SupCarrierGoToMedical::~SupCarrierGoToMedical() { }



void SupCarrierGoToMedical::Transform(NPC* pn) {

	SupplyCarrier* sc = (SupplyCarrier*)pn;
	OnExit(sc);
	if (sc->getHP() <= 0.2*MAX_HP) {

		sc->setCurrentState(new SupCarrierGettingMedicine());
	}
	else if(sc->getMedicineStock() <=0.2*MAX_MEDICINE_STOCK){
		sc->setCurrentState(new SupCarrierGettingMedicineStock());
	}
	else{
		sc->setCurrentState(new SupCarrierIdle());

	}
	sc->getCurrentState()->OnEnter(sc);


}
void SupCarrierGoToMedical::OnEnter(NPC* pn) {
	pn->setDestination(x, y);
	pn->setIsMoving(true);
	pn->setIsSearching(true);
}
void SupCarrierGoToMedical::OnExit(NPC* pn) {
	pn->setIsMoving(false);
	pn->setIsSearching(false);


}
