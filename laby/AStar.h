#pragma once
#include "def.h"

typedef struct NODEA {
	NODEA *father;
	int f,g,h,x,y;
	bool open;
}NODE,*LPNODE;

LPNODE CreateLpn(int g, int h, int x, int y, LPNODE father);

typedef struct WAYNODEA{
	int x, y;
	WAYNODEA *next;
}*WAY, *LPWAYNODE, WAYNODE;

class AStar {
public:
	LPNODE lastNode;
	AStar(Map *m);
	~AStar();
	void FindWay(int sx,int sy,int ex, int ey);
	WAY GetWay();
private:
	Map *m;
	WAY way;
	LPNODE open[MAPEDGE][MAPEDGE];
	int sx, sy, ex, ey;
	int GetH(int x, int y);
	void Open(int x, int y, LPNODE father);
	void SetWay();
	void Clear();
	
};
