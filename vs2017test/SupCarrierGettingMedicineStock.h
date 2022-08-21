#pragma once
#include "State.h"
#include "SupplyCarrier.h"
class SupCarrierGettingMedicineStock :
	public State
{
public:
	SupCarrierGettingMedicineStock();
	~SupCarrierGettingMedicineStock();
	void Transform(NPC* pn);
	void OnEnter(NPC* pn);
	void OnExit(NPC* pn);


};

