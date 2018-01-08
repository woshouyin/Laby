#pragma once
#include "def.h"
#include "MapRender.h"

typedef struct BlockA {
	int x, y;
	struct BlockA *forward;
	struct BlockA *next[3];
}BLOCK, *LPBLOCK, *TREE;

class TreeMapRender :public MapRender {
public:
	TreeMapRender(long seed, Map* map);
	~TreeMapRender();
	void CreateMap(int startX, int startY);
private:
	LPBLOCK blocks[MAPEDGE][MAPEDGE];
	TREE tree;
	TREE CreateTree(int startX, int startY);
	void DestoryWall(LPBLOCK b); // 递归调用，循环路径树，添加AB墙
};