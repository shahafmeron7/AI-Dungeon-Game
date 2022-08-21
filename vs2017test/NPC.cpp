#include "NPC.h"
#include "glut.h"
#include <math.h>
#include "GoToMedical.h"



NPC::NPC(int x,int y,  Room rooms[NUM_ROOMS],vector <Medical*> medicals, vector <Armory*> armories)
{
	
	for (int i = 0; i < NUM_ROOMS; i++)
	{
		this->rooms[i] = rooms[i];
	}
	this->medicals = medicals;
	this->armories = armories;
	this->x = x;
	this->y = y;
	hp = MAX_HP;
}

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::DoSomeThing(int maze[MSZ][MSZ])
{
	
	
}

void NPC::setTargetEnemy()
{
	index_target = rand() % NUM_PLAYERS;
	targetX = enemyTeam.at(index_target)->getCol();
	targetY = enemyTeam.at(index_target)->getRow();

}



void NPC::AstarSearch(int maze[MSZ][MSZ],int xTarget,int yTarget)
{
	Cell* startingCell = new Cell(y, x,nullptr, 0, yTarget, xTarget);

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
		if (pcurrent->getRow() == yTarget && pcurrent->getCol() == xTarget)
		{
			RestorePath(pcurrent);
			return;
		}
		// remove current from pq and paint it black (remove it from grays)
		pq.pop();
		blacks.push_back(*pcurrent);
		// remove it from grays
		itr = find(grays.begin(), grays.end(), *pcurrent); // Cell must have operator ==
		if (itr == grays.end()) // current cell wasn't found: ERROR
		{
			return;
		}
		grays.erase(itr);

		// now check the neighbor cells
		currentRow = pcurrent->getRow();
		currentCol = pcurrent->getCol();
		if (currentRow > 0) // UP
			CheckNeighbor(maze, currentRow - 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentRow < MSZ - 1) // DOWN
			CheckNeighbor(maze, currentRow + 1, currentCol, pcurrent, pq, grays, blacks);
		if (currentCol > 0) // LEFT
			CheckNeighbor(maze, currentRow, currentCol - 1, pcurrent, pq, grays, blacks);
		if (currentCol < MSZ - 1) // RIGHT
			CheckNeighbor(maze,currentRow, currentCol + 1, pcurrent, pq, grays, blacks);
	} // while
	// We shouldn't reach this point normally
	cout << "Error: PQ is empty for find path\n";
}

void NPC::CheckNeighbor(int maze[MSZ][MSZ],int row, int col, Cell * pcurrent, priority_queue<Cell, vector<Cell>, CompareCells>& pq, vector<Cell>& grays, vector<Cell>& blacks)
{
	double cost, cheap = 0.1, expensive = INT_MAX;
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
				while (!pq.empty() && !((*pn) == pq.top()))
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
void NPC::RestorePath(Cell* ps)
{
	this->path.clear();
	while (ps->getParent() != nullptr)
	{
		//maze[ps->getRow()][ps->getCol()] = PATH;
		this->path.push_back(ps);
		ps = ps->getParent();
	}
}

bool NPC::gotHit()
{
	hp -= 50;
	if (hp <= 0) {
		return true;
	}
	return false;

}


bool NPC::BFSIteration(int maze[MSZ][MSZ])
{
	
	//starting cell is the location of the player
	Cell* pCurrent = new Cell(y, x, nullptr);
	vector <Cell> grays;
	vector <Cell> blacks;
	grays.push_back(*pCurrent);
	int row, col; // current row and col
	// check the grays queue
	while(!grays.empty()){
		// pick and remove from grays QUEUE the first Cell and check its neighbors
		pCurrent = new Cell(*grays.begin());
		grays.erase(grays.begin());

		row = pCurrent->getRow();
		col = pCurrent->getCol();
		
		// paint current cell it black
		blacks.push_back(*pCurrent);

		// now scan all the white [or target] neighbors and add them (if it's not a target) to Grays
		// check UP
		if ((row > 0 && CheckNeighborBFS(maze, pCurrent, grays, blacks, row + 1, col)) ||
			//check down
			(row < MSZ - 1 && CheckNeighborBFS(maze, pCurrent, grays, blacks, row - 1, col)) ||
			//check left
			(col > 0 && CheckNeighborBFS(maze, pCurrent, grays, blacks, row, col - 1)) ||
			//check right
			(col < MSZ - 1 && CheckNeighborBFS(maze, pCurrent, grays, blacks, row, col + 1)))
			return true;
		//if soldier looking for enemey and he is not in the room need to change state.
		if(searchingEnemyInRoom && grays.size()>15) return false;
	}		
	return false;
}

bool NPC::CheckNeighborBFS(int maze[MSZ][MSZ], Cell * pCurrent, vector<Cell>& grays, vector<Cell>& blacks, int row, int col)
{
	vector <Cell>::iterator itrb;
	vector <Cell>::iterator itrg;
	// check if the niegbor is not a TARGET

	Cell* pn = new Cell(row, col, pCurrent);
	// check color of theis cell
	itrb = find(blacks.begin(), blacks.end(), *pn);
	itrg = find(grays.begin(), grays.end(), *pn);

	//found target(cover) in case Im looking for cover and not enemy
	//OR
	//in case im looking for enemy and he is nearby
	if (!searchingEnemyInRoom && maze[row][col] == COVER) {
		RestorePath(pn);
		return true;
	}

	if (searchingEnemyInRoom && checkIfTargetIsNearby(ENEMY)) {
		RestorePath(pn);
		return true;
	}
	//if im in path or space(white)
	if (maze[row][col] != WALL) {

		for (int i = 0; i < blacks.size(); i++)
		{
			if (blacks.at(i).getRow() == row && blacks.at(i).getCol() == col)
				return false;
		}
		for (int i = 0; i < grays.size(); i++)
		{
			if (grays.at(i).getRow() == row && grays.at(i).getCol() == col)
				return false;
		}
		grays.push_back(*pn);
	}
	
	
}

void NPC::setDestination(double destX, double destY)
{
	targetX = destX;
	targetY = destY;
}
bool NPC::checkIfTargetIsNearby(int targetObject)
{
	//if im searching for enemy I need to get the updated coordinates of enemy soldier so see if he is nearby
	//loop to check whether enemy soldier is in my room
	if (targetObject == ENEMY) {
		for (int i = 0; i < NUM_PLAYERS; i++)
		{
			if (enemyTeam.at(i) != nullptr) {

				int tCol = enemyTeam.at(i)->getCol();
				int tRow = enemyTeam.at(i)->getRow();
				if (fabs(x - tCol) < 5 && fabs(y - tRow) < 5) {
					//setting the target coordiantes
					targetY = tRow;
					targetX = tCol;
					return true;
				}
			}
		}
		return false;
	}
	//else check whether I nearby medical/armory (the supply carrier is dead)
	else return fabs(x - targetX) < 1 && fabs(y - targetY) < 1;
	
}


void NPC::DrawMe(int team)
{
	

}


