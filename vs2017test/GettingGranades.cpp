#include "GettingGranades.h"
#include "Soldier.h"
#include "Idle.h"
GettingGranades::GettingGranades()
{
}

GettingGranades::~GettingGranades()
{
}

void GettingGranades::Transform(NPC * pn)
{
	OnExit(pn);
	//if im here it means im getting grenades from supply carrier
	//if (pn->getInterruptedState()) {
	//	pn->setCurrentState(pn->getInterruptedState());
	//}
	////else im in armory , going back idle
	//else {
	//	pn->setCurrentState(new Idle());
	//}
	pn->setCurrentState(new Idle());

	pn->getCurrentState()->OnEnter(pn);
}

void GettingGranades::OnEnter(NPC * pn)
{
	pn->setIsGettingGranades(true);
}

void GettingGranades::OnExit(NPC * pn)
{
	pn->setIsGettingGranades(false);

}
