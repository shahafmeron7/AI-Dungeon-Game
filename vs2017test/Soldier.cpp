#include "Soldier.h"
#include "GoToMedical.h"
#include "Idle.h"
Soldier::Soldier(int x, int y, Room rooms[NUM_ROOMS], vector<Medical*> medicals, vector<Armory*> armories,SupplyCarrier* sc) : NPC(x,y,rooms,medicals,armories)
{
	this->sc = sc;
	ammo = MAX_AMMO;
	startShooting = false;
	bullet = nullptr;
	grenade = nullptr;
	inCover = false;
	granades = MAX_GRANADES;
	pCurrentState = new Idle();
	pCurrentState->OnEnter(this);
}

Soldier::Soldier()
{
}

Soldier::~Soldier()
{
}

void Soldier::DoSomeThing(int maze[MSZ][MSZ])
{

		if (isMoving)
		{
			//check which kind of target soldier need to find
			//int targetObject = this->getSupplyCarrier() != nullptr ? ENEMY : SUPPLY;
			//if I already found the path to target, need to move by one.
			if (this->path.size() > 0) {
				//if soldier in the middle of the way but there is enemy soldier near him, soldier need to engage
				if (checkIfTargetIsNearby(ENEMY) && !needSupply && !inPass) {
					this->path.clear();
					isMoving = false;
					//realistic choice if throw grenade or shoot bullets
					int choice = rand() % 30;
					if (choice >15) {
						isThrowingGranade = true;
					}
					else {
						isShooting = true;

					}
					pCurrentState->Transform(this);
					return;
				}
				x = this->path[this->path.size() - 1]->getCol();
				y = this->path[this->path.size() - 1]->getRow();
				this->path.pop_back();
				if (this->path.size() == 0 && needSupply) {
					//soldier reached cover
					inCover = true;
				}
			}
			//else I need to search the target using Astar.
			else if (searching) {
				this->AstarSearch(maze, this->targetX, this->targetY);
				this->searching = false;
				
			}
			else if (searchingEnemyInRoom) {
				//add BFS search in the room for nearset target position
				this->BFSIteration(maze);
				searchingEnemyInRoom = false;
			}
			else if (goingToCover) {
				this->BFSIteration(maze);
				//add BFS search in the room for nearset cover position
				this->goingToCover = false;
				this->needSupply = true;
			}
			//else I need to transform to next state.
			else {
				inCover = false;
				pCurrentState->Transform(this);

			}
		}
		else// player not in movement, need to check if he is getting ammo,medicine,chasing player,runing from player.
		{
			if (isIdle) {
				pCurrentState->Transform(this);

			}
			if (isShooting) {
				//check if enemy still on sight or if im at path im not allowed to shoot
				int c = this->getCol();
				int r = this->getRow();

				if (!checkIfTargetIsNearby(ENEMY) || maze[r][c]==PASS) {
					isShooting = false;
					inPass = true;
					count_bullet_not_hit_target = 0;
					pCurrentState->Transform(this);
					return;
				}
				//if soldier dont hit target, maybe target is in cover, need to change state.
				if (count_bullet_not_hit_target > 3) {
					count_bullet_not_hit_target = 0;
					pCurrentState->Transform(this);
					return;
				}
				soldierShooting(maze);
				//if soldier in combat and have low hp or ammo, need to change state(maybe running or go to cover)
				if (hp <= 0.2*MAX_HP || ammo <= 0.2*MAX_AMMO) {
					startShooting = false;
					count_bullet_not_hit_target = 0;
					pCurrentState->Transform(this);
				}
			}
			if (isThrowingGranade) {
				int c = this->getCol();
				int r = this->getRow();
				if (maze[r][c] == PASS) {
					isThrowingGranade = false;
					inPass = true;
					pCurrentState->Transform(this);
					return;
				}
				soldierThrowing(maze);
				//if soldier in combat and have low hp or granades, need to change state(maybe running or go to cover)
				if (granades <= 0.5*MAX_GRANADES) {
					startThrowing = false;
					pCurrentState->Transform(this);
				}
			}

			//If soldier need supply and the SC is reach the soldier or SC is dead, only then transform.
			if (needSupply) {
				
				if(checkIfSupCarrierHere() || this->sc==nullptr)
				//need to transform to state of getting ammo/granades/medicine
					pCurrentState->Transform(this);

			}
			if (isGettingMedicine) {
				if (!checkIfSupCarrierHere()) {
					pCurrentState->Transform(this);
					return;
				}
				hp += 10;

				// check if the NPC should do something else
				if (hp >= MAX_HP)
					pCurrentState->Transform(this);

			}
			
			if (isGettingGranades) {
				if (!checkIfSupCarrierHere()) {
					pCurrentState->Transform(this);
					return;

				}
				granades++;
				// check if the NPC should do something else
				if (granades >= MAX_GRANADES)
					pCurrentState->Transform(this);

			}
			

			if (isGettingAmmo)
			{
				if (!checkIfSupCarrierHere()) {
					pCurrentState->Transform(this);
					return;

				}
				ammo++;
				// check if the NPC should do something else
				if (ammo >= MAX_AMMO)
					pCurrentState->Transform(this);
			}


		}
}

void Soldier::soldierShooting(int maze[MSZ][MSZ])
{
	if (startShooting) {
		if (bullet == nullptr) {
			startShooting = false;
			ammo--;
			return;
		}

		//size of ammo minus one bullet
		if (!bullet->getIsMoving()) {
			//if the bullet reach wall/cover/target, we need to load next bullet and decrease the magazine ammo
			ammo--;
			bullet = nullptr;
			startShooting = false;
		}
	}
	else {
		//first iteration need to update all bullets direction to target
		//calc coordinates of start positon of bullet by the soldier location

		double angle = atan2(targetY - y, targetX - x);
		bullet = new Bullet(x, y, angle);
		bullet->Fire();
		startShooting = true;
	}
	
	
}
void Soldier::soldierThrowing(int maze[MSZ][MSZ])
{
	if (startThrowing) {
		//size of grenades minus one grenade
		if (grenade->getIsExploded()) {
			//if the bullet reach wall/cover/target, we need to load next bullet and decrease the magazine ammo
			granades--;
			grenade = nullptr;
			startThrowing = false;
		}
	}
	else {
		
		//loading grenade, prepraing to shoot
		grenade = new Grenade(x, y);
		grenade->Explode();
		startThrowing = true;
	}
}


bool Soldier::checkIfSupCarrierHere()
{
	if (sc == nullptr) return false;
	return fabs(x - sc->getCol()) < 1 && fabs(y - sc->getRow()) < 1;
}


void Soldier::DrawMe(int team)
{
	if (team == PURPLE_TEAM) {
		glColor3d(0.5, 0, 0.5);
	}
	//green team
	else {
		glColor3d(0, 1, 0);

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

	// stack ammo
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 1.5, y);
	glVertex2d(x - 1.5, y - 1);
	glVertex2d(x - 1, y - 1);
	glVertex2d(x - 1, y);
	glEnd();
	// draw ammo
	for (int i = 0; i < ammo / 5; i++)
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
	for (int i = 0; i < granades / 0.2; i++) {

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

