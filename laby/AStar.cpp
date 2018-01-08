#include <windows.h>
#include <math.h>
#include <iostream>
#include "AStar.h"
#include "map.h"

LPNODE CreateLpn(int g, int h, int x, int y, LPNODE father) {
	LPNODE lpn = new NODE;
	lpn->f = g + h;
	lpn->g = g;
	lpn->h = h;
	lpn->x = x;
	lpn->y = y;
	lpn->father = father;
	return lpn;
}

AStar::AStar(Map *m) {
	AStar::m = m;
	AStar::ex = 0;
	AStar::ey = 0;
	AStar::sx = 0;
	AStar::sy = 0;
	AStar::way = NULL;
	AStar::lastNode = NULL;
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE; t++) {
			AStar::open[i][t] = CreateLpn(0, 0, i, t, NULL);
		}
	}
}

AStar::~AStar() {
	Clear();
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE; t++) {
			delete open[i][t];
			open[i][t] = NULL;
		}
	}
	lastNode = NULL;
	way = NULL;
}

void AStar::Open(int x, int y, LPNODE father) {
	open[x][y]->father = father;
	open[x][y]->g = father->g + 1;
	open[x][y]->h = GetH(x, y);
	open[x][y]->f = open[x][y]->h + open[x][y]->g;
	open[x][y]->open = true;
}

void AStar::FindWay(int x1, int y1, int x2, int y2) {
	int x, y, tx, ty;
	Clear();
	sx = x1;
	sy = y1;
	ex = x2;
	ey = y2;
	open[sx][sy]->g = 0;
	open[sx][sy]->h = GetH(sx,sy);
	open[sx][sy]->f = open[sx][sy]->g + open[sx][sy]->h;
	open[sx][sy]->open = true;
	do {
		lastNode = NULL;
		for (int i = 0; i < MAPEDGE; i++) {
			for (int t = 0; t < MAPEDGE; t++) {
				if (open[i][t]->open) {
					if (lastNode == NULL) {
						lastNode = open[i][t];
						x = i;
						y = t;
					}
					else {
						if (lastNode->f > open[i][t]->f) {
							lastNode = open[i][t];
							x = i;
							y = t;
						}
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			tx = x;
			ty = y;
			switch(i){
			case 0:
				if (m->GetAWall(x, y) == 0) {
					ty--;
				}
				break;
			case 1:
				if (m->GetAWall(x, y + 1) == 0) {
					ty++;
				}
				break;
			case 2:
				if (m->GetBWall(x, y) == 0) {
					tx--;
				}
				break;
			case 3:
				if (m->GetBWall(x + 1, y) == 0) {
					tx++;
				}
				break;
			}
			if ((x != tx || y != ty) && tx >= 0 && tx < MAPEDGE && ty >= 0 && ty < MAPEDGE) {
				if (!open[tx][ty]->open && open[tx][ty]->f == -1) {
					Open(tx, ty, lastNode);
				}
			}
		}
		lastNode->open = false;
	}while (lastNode->x == ex && lastNode->y == ey);
	SetWay();
}

WAY AStar::GetWay() {
	return way;
}

int AStar::GetH(int x, int y)
{
	return abs(x - ex) + abs(y - ey);
}

void AStar::SetWay() {
	LPWAYNODE lpw = NULL;
	LPNODE lpn = lastNode;
	do{
		lpw = new WAYNODE;
		lpw->x = lpn->x;
		lpw->y = lpn->y;
		lpw->next = way;
		way = lpw;
	}while (lpn = lpn->father);
}

void AStar::Clear() {
	LPWAYNODE lpw = NULL;
	if (way != NULL) {
		while (way = way->next) {
			delete lpw;
			lpw = way;
		}
		delete lpw;
	}
	for (int i = 0; i < MAPEDGE; i++) {
		for (int t = 0; t < MAPEDGE; t++) {
			AStar::open[i][t]->father = NULL;
			AStar::open[i][t]->open = false;
			AStar::open[i][t]->f = -1;
			AStar::open[i][t]->g = -1;
			AStar::open[i][t]->h = -1;
		}
	}
}