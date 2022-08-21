#include "glut.h"

#include <time.h>
#include <vector>
#include <queue>
#include <iostream>
#include "Room.h"
#include "Cell.h"
#include <cmath>
#include <Windows.h>

#include "CompareCells.h"
#include "Bullet.h"
#include "Grenade.h"
#include "NPC.h"
#include "Definitions.h"
#include "Medical.h"
#include "Armory.h"
#include "GoToMedical.h"
#include "GoToArmory.h"
#include "SupplyCarrier.h"
#include "Soldier.h"
#include <math.h>
#include "main.h"
#include <string>


using namespace std;

int maze[MSZ][MSZ] = { 0 };
double security_map[MSZ][MSZ] = { 0 };
double visibility_map[MSZ][MSZ] = { 0 };

Room rooms[NUM_ROOMS];
vector <Medical*> medicalCenters;
vector <Armory*> armories;
vector <NPC*> purpleTeam;
vector <NPC*> greenTeam;

bool underConstruction = true;
bool gameEnded = false;
int r1=0, r2=1; // rooms indices

void SetupRooms();
void DigPassages();
void AddObstacles();
void addPlayers();
void addMedicalCenter();
void addArmories();
void DigPath(int index1, int index2);
void updateTeamThatSupplyCarrierIsDead(vector<NPC*>& enemyTeam);
void checkIfGameEnded();
void updateTeamStats(vector<NPC*>& team, vector<NPC*>& enemyTeam);
void init()
{	//          Red Green Blue 
	glClearColor(0, 0, 0.4, 0);// color of window background
	// set the main axes
	glOrtho(0, MSZ, 0, MSZ ,- 1, 1); 

	srand(time(0));

	SetupRooms();
//	DigPassages();
	AddObstacles();
	addMedicalCenter();
	addArmories();
	addPlayers();
	while (underConstruction)
	{
		DigPath(r1, r2);
		// prepare for the next A*
		r2++;
		if (r2 >= NUM_ROOMS)
		{
			r1++;
			r2 = r1 + 1;
			if (r1 + 1 >= NUM_ROOMS)
				underConstruction = false;
		}
	}
	

}

void AddObstacles()
{
	for (int i = 0; i < NUM_ROOMS; i++) {
		int num_obstacles = rand() % 12;
		Room room = rooms[i];
		int xr = room.getCenterX();
		int yr = room.getCenterY();
		int wr = room.getWidth();
		int hr = room.getHeight();
		//initial random position inside the room bounderis. 
		for (int j = 0; j < num_obstacles; j++) {
			int new_x = xr - wr / 2 + rand() % wr;
			int new_y = yr - hr / 2 + rand() % hr;
			maze[new_y][new_x] = COVER;
		}
	}
}

void addArmories() {
	for (int i = 0; i < NUM_ARMORIES; i++)
	{
		Room room = rooms[rand() % NUM_ROOMS];
		int xr = room.getCenterX();
		int yr = room.getCenterY();
		int wr = room.getWidth();
		int hr = room.getHeight();
		//initial random position inside the room bounderis. 
		int new_x = xr - wr / 2 + rand() % wr;
		int new_y = yr - hr / 2 + rand() % hr;
		armories.push_back(new Armory(new_x, new_y));
		
	}
}
void addMedicalCenter()
{
	for (int i = 0; i < NUM_MEDICAL_CENTERS; i++)
	{
		Room room = rooms[rand() % NUM_ROOMS];
		int xr = room.getCenterX();
		int yr = room.getCenterY();
		int wr = room.getWidth();
		int hr = room.getHeight();
		//initial random position inside the room bounderis. 
		int new_x = xr - wr / 2 + rand() % wr;
		int new_y = yr - hr / 2 + rand() % hr;
		medicalCenters.push_back(new Medical(new_x, new_y));
	}

}

void addPlayers()
{

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		Room room1 = rooms[0];
		int xr = room1.getCenterX();
		int yr = room1.getCenterY();
		int wr = room1.getWidth();
		int hr = room1.getHeight();
		Room room2 = rooms[NUM_ROOMS - 1];
		int xr2 = room2.getCenterX();
		int yr2 = room2.getCenterY();
		int wr2 = room2.getWidth();
		int hr2 = room2.getHeight();
		//initial random position inside the room bounderis. 
		int new_x = xr - wr / 2 + rand() % wr;
		int new_y = yr - hr / 2 + rand() % hr;
		int new_x2 = xr2 - wr2 / 2 + rand() % wr2;
		int new_y2 = yr2 - hr2 / 2 + rand() % hr2;
		if (i == 0) {
			SupplyCarrier* sc = new SupplyCarrier(new_x, new_y,rooms, medicalCenters, armories);
			SupplyCarrier* sc2 = new SupplyCarrier(new_x2, new_y2, rooms, medicalCenters, armories);

			purpleTeam.push_back(sc);
			greenTeam.push_back(sc2);

		}
		else {
			//adding new soldier with the pointer to SupplyCarrier
			Soldier* s = new Soldier(new_x, new_y, rooms, medicalCenters, armories, (SupplyCarrier*)purpleTeam.at(0));
			Soldier* s2 = new Soldier(new_x2, new_y2, rooms, medicalCenters, armories, (SupplyCarrier*)greenTeam.at(0));

			purpleTeam.push_back(s);
			greenTeam.push_back(s2);

		}
	}
		//supply carrirers needs to know their teammates
		purpleTeam.at(0)->setTeam(purpleTeam);
		greenTeam.at(0)->setTeam(greenTeam);
		//setting enemy team for each soldiers of the other team (to know the targets)
		for (int i = 1; i < NUM_PLAYERS; i++)
		{
			
			purpleTeam.at(i)->setEnemyTeam(greenTeam);
			//setting random target from the enemy team
			greenTeam.at(i)->setEnemyTeam(purpleTeam);
			//setting random target from the enemy team


		}


}




// checks for overlapping with rooms of lower indices
bool HasOverlap(int w, int h, int x, int y, int index)
{
	bool overlaps = false;
	int i;
	int dx, dy,gap=4;

	for (i = 0; i < index && !overlaps; i++)
	{
		dx = abs(rooms[i].getCenterX() - x);
		dy = abs(rooms[i].getCenterY() - y);
		if (dx < w / 2 + rooms[i].getWidth() / 2 + gap && dy < h / 2 + rooms[i].getHeight() / 2 + gap)
			overlaps = true;
	}
	return overlaps;
}

void SetupRooms()
{
	int w, h, x, y;
	for (int r = 0; r < NUM_ROOMS; r++)
	{
		do
		{
			w = 8 + rand() % 25;
			h = 8 + rand() % 25;		
			x = 2 + w / 2 + rand() % (MSZ - 4 - w);
			y = 2 + h / 2 + rand() % (MSZ - 4 - h);
		} while (HasOverlap(w,h,x,y,r));
		rooms[r].setWidth(w);
		rooms[r].setHeight(h);
		rooms[r].setCenterX(x);
		rooms[r].setCenterY(y);

		rooms[r].AddMeToMaze(maze);
	}
}

// if the neighbor cell is white  (including target as wll) then add it to pq and paint it gray
// if it is black then do nothing
// if it is gray (it can be target as wll) check 2 cases:
//         1: if F of the new found neghbor isn't better (>=) then of the previously found cell then do notheing
//         2: if  F of the new found neghbor IS better (<) then we have to update the cell parameters!!!

void CheckNeighbor(int row, int col, Cell* pcurrent, priority_queue <Cell, vector<Cell>, CompareCells>&pq,
	vector <Cell> &grays, vector <Cell>&blacks)
{
	double cost,cheap = 0.1, expensive = 0.4;
	vector <Cell>::iterator itrb;
	vector <Cell>::iterator itrg;


	if (maze[row][col] == SPACE || maze[row][col] == PASS) cost = cheap;
	else cost = expensive;

	// create neighbor cell
	Cell* pn = new Cell(row, col, pcurrent, pcurrent->getG() + cost, pcurrent->getTargetRow(), pcurrent->getTargetCol());
	// check color of theis cell
	itrb = find(blacks.begin(), blacks.end(), *pn);
	itrg = find(grays.begin(), grays.end(), *pn);

	// if it is white
	if (itrb == blacks.end() && itrg == grays.end())
	{
		pq.push(*pn);
		grays.push_back(*pn);
	}
	else  // it must be either gray or black 
		if (itrg != grays.end())
	{
		if (pn->getF() < itrg->getF()) // we have to update it
		{
			grays.erase(itrg);
			grays.push_back(*pn);
			// to update (find) pn in pq we need manually to extract all the cells that stand bfore pn in pq including pn
			// to update it and then to push all of them back to pq
			vector <Cell> tmp;
			while(!pq.empty() && !((*pn)== pq.top()))
			{
				tmp.push_back(pq.top());
				pq.pop();
			}
			if (pq.empty())
				cout << " neighbor wasn't found in pq \n";
			else // *pn is now at top of pq
			{
				pq.pop();
				pq.push(*pn);
				// move back to pq all the cells from tmp
				while (!tmp.empty())
				{
					pq.push(tmp.back());
					tmp.pop_back();
				}
			}
		}
	}

}

void RestorePath(Cell* ps)
{
	while (ps->getParent() != nullptr)
	{
		if (maze[ps->getRow()][ps->getCol()] == WALL)
			maze[ps->getRow()][ps->getCol()] = PASS;
		ps = ps->getParent();
	}
}

// creates path from rooms[index1] to rooms[index2] using A*
void DigPath(int index1, int index2)
{
	Cell* startingCell = new Cell(rooms[index1].getCenterY(), rooms[index1].getCenterX(),
		nullptr, 0, rooms[index2].getCenterY(), rooms[index2].getCenterX());

	Cell* pcurrent = nullptr;
	int currentRow, currentCol;

	priority_queue <Cell, vector<Cell>, CompareCells> pq;
	vector <Cell> grays;
	vector <Cell> blacks;

	vector <Cell>::iterator itr;


	// add Start Cell to pq and paint it gray
	pq.push(*startingCell);
	grays.push_back(*startingCell);

	// start A* . In our case pq shouldn't be empty because we should find the target before all the 
	// cells are over
	while (!pq.empty())
	{
		// pq is not empty so pick the top Cell
		pcurrent = new Cell(pq.top());
		// check if current is target
		if (pcurrent->getRow() == rooms[index2].getCenterY() && pcurrent->getCol() == rooms[index2].getCenterX())
		{
			RestorePath(pcurrent);
			cout << "The path from room " << index1 << " to room " << index2 << " has been found\n";
			return;
		}
		// remove current from pq and paint it black (remove it from grays)
		pq.pop();
		blacks.push_back(*pcurrent);
		// remove it from grays
		itr = find(grays.begin(), grays.end(), *pcurrent); // Cell must have operator ==
		if (itr == grays.end()) // current cell wasn't found: ERROR
		{
			cout << "Error: current wasn't found in grays for room " << index1 << " to room " << index2 << endl;
			return;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			CheckNeighbor(currentRow - 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentRow < MSZ-1) // DOWN
			CheckNeighbor(currentRow + 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentCol > 0) // LEFT
			CheckNeighbor(currentRow , currentCol-1, pcurrent, pq, grays, blacks);
		if (currentCol < MSZ-1) // RIGHT
			CheckNeighbor(currentRow , currentCol+1, pcurrent, pq, grays, blacks);
	} // while
	// We shouldn't reach this point normally
	cout << "Error: PQ is empty for room " << index1 << " to room " << index2 << endl;
}

void DigPassages()
{
	int i, j;

	for (i = 0; i < NUM_ROOMS; i++)
		for (j = i + 1; j < NUM_ROOMS; j++)
			DigPath(i, j);
}



void CreateSecurityMap()
{
	int num_simulations = 500;
	double damage = 0.001;
	int i;
	Grenade* g;

	for (i = 0; i < num_simulations; i++)
	{
		g = new Grenade(rand() % MSZ, rand() % MSZ);
		g->SimulateExplosion(maze, security_map, damage);
	}

}


void ShowMaze() 
{
	int i, j;

	for(i=0;i<MSZ;i++)
		for (j = 0; j < MSZ; j++)
		{
			// set color for cell (i,j)
			switch (maze[i][j]) 
			{
			case WALL:
				glColor3d(0.51, 0.411, 0.32); // dark
				break;
			case COVER:
				glColor3d(0.62, 0.32, 0.17); // brown sieena 
				break;
			case PASS:
				glColor3d(0.85, 0.85, 0.85);
				break;
			case GRAY:
				glColor3d(0.41, 0.41, 0.41);
				break;
			case PATH:
				glColor3d(1, 1, 1);
				break;
			case SPACE:
				double d = security_map[i][j];
				double v = visibility_map[i][j];
				glColor3d(1-d-0.5*v, 1-d, 1-d-0.5*v); // white - security map value - visibility map value
				break;
			
			}// switch
			// now show the cell as plygon (square)
			glBegin(GL_POLYGON);
			glVertex2d(j, i); // left-bottom corner
			glVertex2d(j, i+1); // left-top corner
			glVertex2d(j+1, i+1); // right-top corner
			glVertex2d(j+1, i); // right-bottom corner
			glEnd();
		}// for
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer
	
	ShowMaze();
	
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//team 1 draw soldiers
		if (purpleTeam.at(i) != nullptr)
			if (i == 0)//draw supply carrier
				((SupplyCarrier*)purpleTeam.at(i))->DrawMe(PURPLE_TEAM);
			else //draw soldier
			{
				Soldier* s = (Soldier*)purpleTeam.at(i);
				s->DrawMe(PURPLE_TEAM);
			}
		//team 2 draw soldiers
		if (greenTeam.at(i) != nullptr)
			if (i == 0) //draw supply carrier
				((SupplyCarrier*)greenTeam.at(i))->DrawMe(GREEN_TEAM);
			else //draw soldier
			{
				Soldier* s = (Soldier*)greenTeam.at(i);
				s->DrawMe(GREEN_TEAM);
			}
	}

	//loop to check whether a soldier is in shooting combat..drawing bullets for each team
	// i=1 because supply carrier not shooting.
	for (int i = 1; i < NUM_PLAYERS; i++)
	{
		Soldier* soldierPurpleTeam = (Soldier*)purpleTeam.at(i);
		Soldier* soldierGreenTeam = (Soldier*)greenTeam.at(i);
	
		//check if one of the soldiers of each team is shooting
		if (soldierPurpleTeam!=nullptr && soldierPurpleTeam->getIsShooting() && soldierPurpleTeam->getBullet() != nullptr) {
			soldierPurpleTeam->getBullet()->show();
		}
		if (soldierGreenTeam!=nullptr && soldierGreenTeam->getIsShooting() && soldierGreenTeam->getBullet() != nullptr) {
			soldierGreenTeam->getBullet()->show();
		}
		//check if one of the soldiers of each team is throwing grenades
		if (soldierPurpleTeam != nullptr && soldierPurpleTeam->getIsThrowingGranade() && soldierPurpleTeam->getGrenade() != nullptr) {
			soldierPurpleTeam->getGrenade()->show();
		}
		if (soldierGreenTeam != nullptr && soldierGreenTeam->getIsThrowingGranade() && soldierGreenTeam->getGrenade() != nullptr) {
			soldierGreenTeam->getGrenade()->show();
		}
	}

	for (int i = 0; i < medicalCenters.size(); i++)
		medicalCenters.at(i)->DrawMe();
	for (int i = 0; i < armories.size(); i++)
		armories.at(i)->DrawMe();
	Sleep(40);
	glutSwapBuffers(); // show all
}

void idle()
{
	if (!gameEnded) {
		checkIfGameEnded();
	}
	else {
		return;
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//check soldier if not dead, then change/check state
		if (purpleTeam.at(i) != nullptr)
		{
			// supply carrier at 0
			if (i == 0)
			{
				SupplyCarrier* sc = (SupplyCarrier*)purpleTeam.at(i);
					sc->DoSomeThing(maze);
			}
			else //soldier at 1,2,3
			{
				Soldier* s = (Soldier*)purpleTeam.at(i);
					s->DoSomeThing(maze);
			}
		}
		//checking for team2 the same as above
		if (greenTeam.at(i) != nullptr)
		{
			// supply carrier at 0
			if (i == 0)
			{
				SupplyCarrier* sc = (SupplyCarrier*)greenTeam.at(i);
					sc->DoSomeThing(maze);
			}
			else //soldier at 1,2,3
			{
				Soldier* s = (Soldier*)greenTeam.at(i);
					s->DoSomeThing(maze);
			}
		}
	}
	//loop to move bullet/grenades coordinates in case soldiers in shooting state.
	//i=1 because supply carrier not shooting.
	for (int i = 1; i < NUM_PLAYERS; i++)
	{
		Soldier* soldierPurpleTeam = (Soldier*)purpleTeam.at(i);
		Soldier* soldierGreenTeam = (Soldier*)greenTeam.at(i);
		//move bullet for each soldier that is shooting
		if (soldierPurpleTeam!=nullptr && soldierPurpleTeam->getIsShooting() && soldierPurpleTeam->getBullet()!=nullptr) {
			soldierPurpleTeam->getBullet()->Move(maze,GREEN_TEAM,purpleTeam,greenTeam);
			if (soldierPurpleTeam->getBullet()->getIsBulletHitEnemy()) {
				//bullet become null after hit
				soldierPurpleTeam->setBullet(nullptr);
				//if purple team hit green team, need to check stats of green team and made stats updates
				updateTeamStats(purpleTeam,greenTeam);
			}
			//if bullet stop moving and didnt hit any target it means we missed target so updating count of miss bullet +1
			else if (!soldierPurpleTeam->getBullet()->getIsBulletHitEnemy() && !soldierPurpleTeam->getBullet()->getIsMoving()) {
				soldierPurpleTeam->setBulletDidntHitCount();
			}
			if (soldierPurpleTeam->getBullet() != nullptr && !soldierPurpleTeam->getBullet()->getIsMoving()) {
				soldierPurpleTeam->setBullet(nullptr);

			}
			if(gameEnded) cout << "Purple Team Has Won " <<endl;
			
		}
		if (soldierGreenTeam != nullptr && soldierGreenTeam->getIsShooting() && soldierGreenTeam->getBullet() != nullptr) {
			soldierGreenTeam->getBullet()->Move(maze, PURPLE_TEAM, greenTeam, purpleTeam);
			if (soldierGreenTeam->getBullet()->getIsBulletHitEnemy()) {
				//bullet become null after hit

				soldierGreenTeam->setBullet(nullptr);

				//if green team hit purple team, need to check stats of purple team and made stats updates
				updateTeamStats(greenTeam,purpleTeam);
			}
			//if bullet stop moving and didnt hit any target it means we missed target so updating count of miss bullet +1
			else if(!soldierGreenTeam->getBullet()->getIsBulletHitEnemy() && !soldierGreenTeam->getBullet()->getIsMoving()) {
				soldierGreenTeam->setBulletDidntHitCount();
			}
			//if bullet hit wall/cover set also to null
			if (soldierGreenTeam->getBullet()!=nullptr && !soldierGreenTeam->getBullet()->getIsMoving()) {
				soldierGreenTeam->setBullet(nullptr);

			}
			if (gameEnded) cout << "Green Team Has Won " << endl;

		}
		//move grenades for each soldier that is throwing grenades

		if (soldierPurpleTeam != nullptr && soldierPurpleTeam->getIsThrowingGranade() && soldierPurpleTeam->getGrenade() != nullptr) {
			soldierPurpleTeam->getGrenade()->Exploding(maze, GREEN_TEAM, purpleTeam, greenTeam);
			if (soldierPurpleTeam->getGrenade()->getIsExploded()) {
				updateTeamStats(purpleTeam, greenTeam);
			}
			if (gameEnded) cout << "Purple Team Has Won " << endl;

		}
		if (soldierGreenTeam != nullptr && soldierGreenTeam->getIsThrowingGranade() && soldierGreenTeam->getGrenade() != nullptr) {
			soldierGreenTeam->getGrenade()->Exploding(maze, PURPLE_TEAM, greenTeam, purpleTeam);
			if (soldierGreenTeam->getGrenade()->getIsExploded()) {
				updateTeamStats(greenTeam, purpleTeam);
			}
			if (gameEnded) cout << "Green Team Has Won " << endl;

		}
	}
	
	glutPostRedisplay(); // indirect call to refresh function (display)
}

void updateTeamStats(vector<NPC*>& team, vector<NPC*>& enemyTeam) {

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//if supplycarrier is dead from enemy team updating all enemy team teammates
		if (i == 0 && enemyTeam.at(i) == nullptr) {
			updateTeamThatSupplyCarrierIsDead(enemyTeam);
		}
		//if my team hits enemy team im updating all my teammates with new stats of enemy team
		else if (i != 0 && team.at(i) != nullptr) {
			team.at(i)->setEnemyTeam(enemyTeam);
		}
	}
	//update teammates for supply carriers
	if(purpleTeam.at(0)!=nullptr)
		purpleTeam.at(0)->setTeam(purpleTeam);
	if(greenTeam.at(0)!=nullptr)
		greenTeam.at(0)->setTeam(greenTeam);
}
////function to update that supply carrier is dead on the enemy team
void updateTeamThatSupplyCarrierIsDead(vector<NPC*> &team) {
	for (int i = 1; i < NUM_PLAYERS; i++)
	{
		if(team.at(i)!=nullptr)
			((Soldier*)team.at(i))->setSupplyCarrier(nullptr);

	}


}

void checkIfGameEnded() {
	int countPurplePlayersAlive = 0;
	int countGreenPlayersAlive = 0;

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (purpleTeam.at(i) != nullptr)
			countPurplePlayersAlive++;
	}
	if (countPurplePlayersAlive == 0) {
		cout << "Purple Team has lost, all of them are dead !!!!! " << endl;
		gameEnded = true;
		return;
	}
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (greenTeam.at(i) != nullptr)
			countGreenPlayersAlive++;
	}
	if (countGreenPlayersAlive == 0)
	{
		cout << "Green Team has lost, all of them are dead !!!!! " << endl;
		gameEnded = true;
		return;

	}
	//it is a tie
	if (countGreenPlayersAlive < 2 && countPurplePlayersAlive <2) {

		if (purpleTeam.at(0) != nullptr && greenTeam.at(0) != nullptr)
		{
			cout << "Only supply carriers are left for both teams. IT'S A TIE " << endl;
			gameEnded = true;
			return;

		}
	}

}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double buffering for animation
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Dungeons Final Project");

	glutDisplayFunc(display); // sets display function as window refresh function
	glutIdleFunc(idle); // runs all the time when nothing happens

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	if (gameEnded) {
		exit(0);
	}
	glutMainLoop(); // starts window queue of events
}