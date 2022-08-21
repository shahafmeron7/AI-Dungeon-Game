#pragma once
#include "NPC.h"
const int MAX_MEDICINE_STOCK = 50;
const int MIN_MEDICINE_STOCK = 0;


class SupplyCarrier:
	public NPC
{
protected:
	int medicineStock;
	int ammoStock;
	int granadesStock;
	bool isGettingMedicineStock,isWalking, providingAmmo, providingGranades, providingMedicine;

public:
	SupplyCarrier(int x, int y, Room rooms[NUM_ROOMS] ,vector <Medical*> medicals, vector <Armory*> armories);
	SupplyCarrier();
	~SupplyCarrier();
	void DoSomeThing(int maze[MSZ][MSZ]); // kind of MAIN function
	void setIsGettingMedicinceStock(bool value) { isGettingMedicineStock = value; }
	double getMedicineStock() { return medicineStock; }
	double getAmmo() { return ammoStock; }
	double getGranades() { return granadesStock; }
	void setIsWalking(bool value) { isWalking = value; }
	void setProvidingAmmo(bool value) { providingAmmo = value; }
	void setProvidingGranades(bool value) { providingGranades = value; }
	void setProvidingMedicine(bool value) { providingMedicine = value; }
	bool getIsWalking() { return isWalking; }
	void DrawMe(int team);


};

