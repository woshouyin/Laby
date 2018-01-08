#include "def.h"
#pragma once

class MapRender {
public:
	int size;
	long seed;
	Map *map;
	MapRender(long seed, Map *map);
	virtual ~MapRender();
	virtual void CreateMap(int startX, int startY);
protected:
	void CreateSafeFrame();
};