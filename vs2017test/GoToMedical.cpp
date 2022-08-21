#include "GoToMedical.h"
#include "Definitions.h"
#include "GoToArmory.h"
#include "GettingMedicine.h"
#include "SupplyCarrier.h"
#include "Soldier.h"
GoToMedical::GoToMedical(int x, int y) {

	this->x = x;
	this->y = y;

}

GoToMedical::~GoToMedical() {}

//What will be the next state after getting medicine
void GoToMedical::Transform(NPC *pn) {
	// from GoToMedical
	Soldier* s = (Soldier*)pn;
	OnExit(s);
	s->setCurrentState(new GettingMedicine());
	s->getCurrentState()->OnEnter(s);

}
void GoToMedical::OnEnter(NPC * pn)
{
	pn->setIsMoving(true);
	pn->setIsSearching(true);
	pn->setDestination(x, y);
}
void GoToMedical::OnExit(NPC * pn)
{
	pn->setIsMoving(false);
	pn->setIsSearching(false);

}



