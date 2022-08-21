#include "GettingAmmo.h"
#include "Medical.h"
#include "GoToMedical.h"
#include "Idle.h"

using namespace std;
GettingAmmo::GettingAmmo()
{
}

GettingAmmo::~GettingAmmo()
{
}

void GettingAmmo::Transform(NPC * pn)
{
	OnExit(pn);
	//if im here it means im getting ammo from supply carrier
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

void GettingAmmo::OnEnter(NPC * pn)
{
	
	pn->setIsGettingAmmo(true);


}

void GettingAmmo::OnExit(NPC * pn)
{

	pn->setIsGettingAmmo(false);


}
