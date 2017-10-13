#include "def.h"
#pragma once

class Map {
public:
	static Player *players;
	static int playerNum;
	Map(int size);
	~Map();
	void addPlayers(Player* players, int playerNum);
	int HavePlayer(int x, int y);
	void CreateRandomMap(long seed);
	int GetAWall(int x, int y);
	int GetBWall(int x, int y);
	int GetSize();
	int GetEdge();
	void SetAWall(int x, int y, bool wall);
	void SetBWall(int x, int y, bool wall);

private:
	int size;
	int *a;
	int *b;
	int *GetAUnit(int x, int y);
	int *GetBUnit(int x, int y);
	int *GetAUnitByPosition(int x, int y);
	int *GetBUnitByPosition(int x, int y);
};