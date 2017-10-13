#include "def.h"
#pragma once

class MapRender {
public:
	int size;
	long seed;
	Map *map;
	MapRender(long seed, Map *map);
	~MapRender();
	void CreateMap(int startX, int startY);
private:
	void CreateSafeFrame();
};