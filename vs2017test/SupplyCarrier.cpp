#include "SupplyCarrier.h"
#include "SupCarrierIdle.h"

SupplyCarrier::SupplyCarrier(int x, int y,Room rooms[NUM_ROOMS] ,vector<Medical*> medicals, vector<Armory*> armories) : NPC(x,y,rooms,medicals,armories)
{
	this->ammoStock = 0;
	this->medicineStock = 0;
	this->granadesStock = 0;
	pCurrentState = new SupCarrierIdle();
	pCurrentState->OnEnter(this);
}

SupplyCarrier::SupplyCarrier()
{

}

SupplyCarrier::~SupplyCarrier()
{
}

void SupplyCarrier::DoSomeThing(int maze[MSZ][MSZ])
{
	if (isMoving)
	{
		//if I already found the path to target, need to move by one.
		if (this->path.size() > 0) {
			x = this->path[this->path.size()-1]->getCol();
			y = this->path[this->path.size()-1]->getRow();
			this->path.pop_back();
		}
		//else I need to search the target using Astar.
		else if(searching) {
			this->AstarSearch(maze, this->targetX, this->targetY);
			this->searching = false;
		}
		//else I need to transform to next state.
		else {
			pCurrentState->Transform(this);

		}
	}
	else// player not in movement, need to check if he is getting ammo,medicine,chasing player,runing from player.
	{
		if (isGettingMedicine) {
			hp += 0.5;
			// check if the NPC should do something else
			if (hp >= MAX_HP)
				pCurrentState->Transform(this);

		}
		if (isGettingMedicineStock) {
			medicineStock ++;
			// check if the NPC should do something else
			if(medicineStock >=MAX_MEDICINE_STOCK)
				pCurrentState->Transform(this);
		}
		
		if (isGettingGranades)
		{
			granadesStock++;
			// check if the NPC should do something else
			if (granadesStock >= MAX_GRANADES)
				pCurrentState->Transform(this);
		}
		if (isGettingAmmo)
		{
			ammoStock++;
			// check if the NPC should do something else
			if (ammoStock >= MAX_AMMO)
				pCurrentState->Transform(this);
		}
		if (isIdle) {
			pCurrentState->Transform(this);

		}
		if (providingAmmo) {
			ammoStock--;
			// check if the NPC should do something else
			if (ammoStock <= MIN_AMMO)
				pCurrentState->Transform(this);

		}
		if (providingGranades) {
			granadesStock--;
			// check if the NPC should do something else
			if (granadesStock <= MIN_GRANADES)
				pCurrentState->Transform(this);

		}
		if (providingMedicine) {
			medicineStock--;
			// check if the NPC should do something else
			if (medicineStock <= MIN_MEDICINE_STOCK)
				pCurrentState->Transform(this);
		}

	}
}



void SupplyCarrier::DrawMe(int team)
{
	if (team == PURPLE_TEAM) {
		glColor3d(1, 0, 1);
	}
	//green team
	else {
		glColor3d(0.235, 0.7, 0.44);

	}
	// body
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x, y + 0.5);
	glVertex2d(x + 0.5, y);
	glVertex2d(x, y - 0.5);
	glEnd();
	// frame
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 0.5, y);
	glVertex2d(x, y + 0.5);
	glVertex2d(x + 0.5, y);
	glVertex2d(x, y - 0.5);
	glEnd();
	// stack medicine
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 2.5, y);
	glVertex2d(x - 2.5, y - 1);
	glVertex2d(x - 2, y - 1);
	glVertex2d(x - 2, y);
	glEnd();
	// draw medicine
	for (int i = 0; i < medicineStock / 5; i++)
	{
		glColor3d(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x - 2.5, y - 1 + (i)*0.1);
		glVertex2d(x - 2, y - 1 + (i)*0.1);
		glEnd();
	}

	// stack ammo
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 1.5, y);
	glVertex2d(x - 1.5, y - 1);
	glVertex2d(x - 1, y - 1);
	glVertex2d(x - 1, y);
	glEnd();
	// draw ammo
	for (int i = 0; i < ammoStock / 5; i++)
	{
		glColor3d(0.83, 0.68, 0.21);
		glBegin(GL_LINES);
		glVertex2d(x - 1.5, y - 1 + (i)*0.1);
		glVertex2d(x - 1, y - 1 + (i)*0.1);
		glEnd();
	}
	// stack granades
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x + 1.5, y);
	glVertex2d(x + 1.5, y - 1);
	glVertex2d(x + 1, y - 1);
	glVertex2d(x + 1, y);
	glEnd();
	for (int i = 0; i < granadesStock / 0.2; i++) {

		glColor3d(0, 0.65, 0);
		glBegin(GL_LINES);
		glVertex2d(x + 1.5, y - 1 + (i)*0.1);
		glVertex2d(x + 1, y - 1 + (i)*0.1);
		glEnd();
	}

	// hp
	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2d(x - 1, y + 1.5);
	glVertex2d(x - 1 + 2 * hp / MAX_HP, y + 1.5);
	glEnd();
}


