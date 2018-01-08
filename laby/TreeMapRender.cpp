#include <iostream>
#include "TreeMapRender.h"
#include "Map.h"

TreeMapRender::TreeMapRender(long seed, Map* map) : MapRender(seed, map){
	TreeMapRender::seed = seed;
	TreeMapRender::map = map;
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE; t++) {
			blocks[i][t] = new BLOCK;
			blocks[i][t]->x = i;
			blocks[i][t]->y = t;
			blocks[i][t]->forward = NULL;
			blocks[i][t]->next[0] = NULL;
			blocks[i][t]->next[1] = NULL;
			blocks[i][t]->next[2] = NULL;
		}
	}
	size = map->GetSize() * sizeof(int) * 8;
}

TreeMapRender::~TreeMapRender() {
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE; t++) {
			delete blocks[i][t];
		}
	}
}

void TreeMapRender::CreateMap(int startX, int startY){
	srand(seed);
	CreateTree(startX, startY);
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE + 1; t++) {
			map->SetAWall(i, t, true);
			map->SetBWall(t, i, true);
		}
	}
	DestoryWall(tree);

	CreateSafeFrame();
}

LPBLOCK GetUnkonwBlock(LPBLOCK blocks[MAPEDGE][MAPEDGE],int x,int y) {
	if (x >= 0 && x < MAPEDGE && y >= 0 && y < MAPEDGE) {
		if (blocks[x][y]->forward == NULL) {
			return blocks[x][y];
		}
	}
	return NULL;
}

TREE TreeMapRender::CreateTree(int startX, int startY) {
	int nearNum, n;
	LPBLOCK block,forward;
	LPBLOCK nearBlocks[4];
	LPBLOCK wBlocks[MAPEDGE*MAPEDGE] = {NULL};
	tree = blocks[startX][startY];
	wBlocks[0] = tree;
	tree->forward = tree;
	for (int i = 1; i < MAPEDGE * MAPEDGE - 1; i++) {
		
		do {
			//取出一个随机的已存在于 wBlocks 中且未被排除的 LPBLOC0K ,其在 wBlocks 中的索引存入 n ,其本身存入 forward
			while (!(forward = wBlocks[n = rand() % i]));
			nearNum = 0;
			if (nearBlocks[nearNum] = GetUnkonwBlock(blocks, forward->x, forward->y - 1)) {
				nearNum++;
			}
			if (nearBlocks[nearNum] = GetUnkonwBlock(blocks, forward->x, forward->y + 1)) {
				nearNum++;
			}
			if (nearBlocks[nearNum] = GetUnkonwBlock(blocks, forward->x - 1, forward->y)) {
				nearNum++;
			}
			if (nearBlocks[nearNum] = GetUnkonwBlock(blocks, forward->x + 1, forward->y)) {
				nearNum++;
			}
			/*
			if (nearNum == 0) {
				wBlocks[n] = NULL;
			}
			*/
		} while (nearNum == 0);
		block = nearBlocks[rand() % nearNum];
		block->forward = forward;

		if (forward->next[0] == NULL) {
			forward->next[0] = block;
			wBlocks[i] = block;
		}
		else if (forward->next[1] == NULL) {
			forward->next[1] = block;
			wBlocks[i] = block;
		}
		else if (forward->next[2] == NULL) {
			forward->next[2] = block;
			wBlocks[i] = block;
			wBlocks[n] = NULL;
		}
	}
	/*
	int p = 0;
	for (int i = 0; i < MAPEDGE*MAPEDGE; i++) {
		if (wBlocks[i]) {
			cout << "p:" << p++ << " i:" << i << " x:" <<wBlocks[i]->x << " y:" << wBlocks[i]->y << " forward:" << wBlocks[i]->forward << endl;
		}
	}
	*/
	return tree;
}

void TreeMapRender::DestoryWall(LPBLOCK b)
{
	LPBLOCK n;
	for (int i = 0; i < 3; i++) {
		n = b->next[i];
		if (n != NULL) {
			if (b->x == n->x) {
				if (b->y - n->y == 1) {
					map->SetAWall(b->x, b->y, false);
				}
				else {
					map->SetAWall(n->x, n->y, false);
				}
			}
			else {
				if (b->x - n->x == 1) {
					map->SetBWall(b->x, b->y, false);
				}
				else {
					map->SetBWall(n->x, n->y, false);
				}

			}
			DestoryWall(b->next[i]);
		}
	}
}
