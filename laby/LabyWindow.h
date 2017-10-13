#include <windows.h>
#include "def.h"
#pragma once

class LabyWindow {
public:
	static int winner;
	static const int
		wallStartX = 10,
		wallStartY = 70,
		lineWidth = 1,
		lineLong = 20,
		flagX = 31,
		flagY = 15;
	static const COLORREF lineColor = RGB(255, 255, 255);
	LabyWindow(HINSTANCE hinstance, LPSTR name, int width, int height, Map *map);
	~LabyWindow();
	void Run();
	void Init();
	void InitBG();
	void RegisterPlayerImg(int id, LPSTR file);
	bool IsWrong() { return wrong; };
private:
	bool wrong;
	int width, height;
	int mapEdge;
	int PlayerImgSize[5];
	HBITMAP BmpPlayer[5];
	HBITMAP BmpTitle,BmpWin[2];
	HBITMAP BmpFlag;
	HBITMAP BmpTime;
	HINSTANCE hinstance;
	Map *map;
	LPSTR name;
	WNDCLASS wndCls;
	HWND hwnd;
	HDC hdc, hdcMem, hdcBG;
	HBITMAP hbmp, hbmpBG;
	HANDLE threadMSG, threadDraw;
	void Paint();
	void Message();
	void DrawPlayer(int id, int x, int y, int face);
	void DrawWall();
	void DrawWallLine(int type, int x, int y);
	HBITMAP LoadBitmapFromFile(LPSTR file);
	friend DWORD WINAPI Draw(LabyWindow *);

};