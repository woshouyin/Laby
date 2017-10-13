#include <iostream>
#include "MapRender.h"
#include "Map.h"

using namespace std;

MapRender::MapRender(long seed, Map* map) {
	MapRender::seed = seed;
	MapRender::map = map;
	MapRender::size = map->GetSize() * sizeof(int) * 8;
	//cout << size << endl;
}

MapRender::~MapRender() {
}

void MapRender::CreateMap(int startX, int startY) {
	srand(seed);
	for (int i = 0; i < size; i++) {
		for (int t = 0; t < size + 1; t++) {

			//map->SetAWall(i, t, 1);
			//map->SetBWall(t, i, 1);

			map->SetAWall(i, t, rand() % 3 == 1 && rand() % 3 == 2);
			map->SetBWall(t, i, rand() % 3 == 1 && rand() % 3 == 2);
		}
	}


	MapRender::CreateSafeFrame();
}

void MapRender::CreateSafeFrame() {
	for (int i = 0; i < size; i++) {
		for (int t = 0; t < size + 1; t++) {
			if (t == 0 || t == size)
				map->SetAWall(i, t, 1);
			if (t == 0 || t == size)
				map->SetBWall(t, i, 1);
		}
	}
}