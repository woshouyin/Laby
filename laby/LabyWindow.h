#include <windows.h>
#include "def.h"
#pragma once

class LabyWindow {
public:
	static int winner,bottonMode;
	static const int
		wallStartX = 10,
		wallStartY = 70,
		lineWidth = 1,
		lineLong = 20/MAPSIZE,
		flagX = MAPEDGE - 1,
		flagY = MAPEDGE / 2;
	static const int
		bottonWidth = 270,
		bottonHeight = 120,
		bottonX = wallStartX + MAPEDGE*lineLong + 10,
		bottonY = wallStartY + MAPEDGE*lineLong - bottonHeight;
	static const COLORREF lineColor = RGB(100, 100, 50);
	static LabyWindow *labyWin;
	int cs;
	LabyWindow(HINSTANCE hinstance, LPSTR name, int width, int height, Map *map);
	~LabyWindow();
	void Run();
	void Stop();
	void CheckStop();
	void Init();
	void InitBG();
	void RegisterPlayerImg(int id, LPSTR file);
private:
	bool running;
	int width, height;
	int mapEdge;
	int min, sec;
	Timer *sTimer;
	int PlayerImgSize[5];
	HBITMAP BmpPlayer[5];
	HBITMAP BmpTitle,BmpWin[2];
	HBITMAP BmpFlag;
	HBITMAP BmpTime;
	HBITMAP BmpNumber;
	HBITMAP BmpOverTime;
	HBITMAP BmpClock;
	HBITMAP BmpBotton[3];
	HCURSOR BmpIconMouse;
	HCURSOR BmpIconTitle;
	HINSTANCE hinstance;
	Map *map;
	LPSTR name;
	WNDCLASS wndCls;
	HWND hwnd;
	HDC hdcShow, hdcMem, hdcBG;
	HBITMAP hbmp, hbmpBG;
	HANDLE threadMSG, threadDraw;
	AStar *as;
	void Paint();
	void Message();
	void DrawPlayer(int id, int x, int y, int face);
	void DrawWall(HDC hdc);
	void DrawWallLine(HDC hdc, int type, int x, int y);
	HBITMAP LoadBitmapFromFile(LPSTR file);
	friend DWORD WINAPI Draw(LabyWindow *);

};