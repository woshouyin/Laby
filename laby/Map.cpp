#include "Map.h"
#include "Laby.h"
#include "Player.h"
#include "LabyWindow.h"
#include "MapRender.h"

Player *Map::players = NULL;
int Map::playerNum = 0;

Map::Map(int size) {
	Map::size = size;
	do {
		a = (int *)malloc((8 * sizeof(int)*size + 1)*size * sizeof(int));
		b = (int *)malloc((8 * sizeof(int)*size + 1)*size * sizeof(int));
		if (!a || !b) {
			free(a);
			free(b);
		}
	} while (!a || !b);
	for (int i = 0; i < size * (size + 1); i++) {
		*(a + i) = 0;
		*(b + i) = 0;
	}
}

Map::~Map() {
	free(a);
	free(b);
}

int *Map::GetAUnitByPosition(int x, int y) {
	int ux = x / (8 * (int)sizeof(int));
	return GetAUnit(ux, y);
}

int *Map::GetBUnitByPosition(int x, int y) {
	int uy = y / (8 * sizeof(int));
	return GetBUnit(x, uy);
}

int Map::GetAWall(int x, int y) {
	int d = x % (8 * sizeof(int));
	return GetBit(*GetAUnitByPosition(x, y), d);
}

int Map::GetBWall(int x, int y) {
	int d = y % (8 * sizeof(int));
	return GetBit(*GetBUnitByPosition(x, y), d);
}

void Map::SetAWall(int x, int y, bool wall) {
	int d = x % (8 * sizeof(int));
	int *unit = GetAUnitByPosition(x, y);
	if (wall) {
		*unit |= 1 << d;
	}
	else {
		*unit = ~((~*unit) | (1 << d));
	}

}

void Map::SetBWall(int x, int y, bool wall) {
	int d = y % (8 * sizeof(int));
	int *unit = GetBUnitByPosition(x, y);
	if (wall) {
		*unit |= 1 << d;
	}
	else {
		*unit = ~((~*unit) | (1 << d));
	}

	//cout << "x:" << x << " y:" << y << " wall:" << wall << " unit:" << bitset<32>(*unit) << endl;
}

void Map::CreateRandomMap(long seed) {
	MapRender mr(seed, this);
	mr.CreateMap(32,16);
	return;
}

int Map::HavePlayer(int x, int y) {
	for (int i = 0; i < playerNum; i++) {
		if (players[i].x == x && players[i].y == y && players[i].MoveAble()) {
			return players[i].id;
		}
	}
	return -1;
}

void Map::addPlayers(Player* players, int playerNum) 
{ 
	Map::players = players; 
	Map::playerNum = playerNum; 
	for (int i = 0; i < playerNum; i++) {
		players[i].map = this;
	}
}

int Map::GetSize() 
{
	return size; 
}

int Map::GetEdge()
{ 
	return size * sizeof(int) * 8; 
}

int *Map::GetAUnit(int x, int y) {
	return a + x + y * size;

}
int *Map::GetBUnit(int x, int y) 
{
	return b + y + x * size; 
}