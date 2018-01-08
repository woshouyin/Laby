#include <windows.h>
#include <iostream>
#include <time.h>
#include "LabyWindow.h"
#include "Timer.h"
#include "Player.h"
#include "Map.h"
#include "Laby.h"

static int edge;

int WINAPI WinMain(_In_ HINSTANCE hinstance
					, _In_opt_ HINSTANCE hPrevInstance
					, _In_ LPSTR lpCmdLine
					, _In_ int nCmdShow) {
	FILE * stream;

	AllocConsole();
	freopen_s(&stream, "conout$", "w", stdout);
	Map *m = new Map(MAPSIZE);
	//m->CreateRandomMap(GetTickCount());
	LabyWindow *lw = new LabyWindow(hinstance, "Laby", 950, 830, m);
	Player ps[2] = { Player(0,0,0,20), Player(1,0,MAPEDGE - 1,20) };
	m->addPlayers(ps, 2);
	lw->RegisterPlayerImg(0, "player1.bmp");
	lw->RegisterPlayerImg(1, "player2.bmp");
	lw->InitBG();
	lw->Init();
	lw->Run();

	delete m;
	delete lw;

	//system("pause");
	return 0;
}

DWORD WINAPI Draw(LabyWindow *lw) {
	while (lw->running) {
		//cout << "Draw" << endl;
		BitBlt(lw->hdcMem, 0, 0, lw->width, lw->height, lw->hdcBG, 0, 0, SRCCOPY);
		lw->Paint();
		BitBlt(lw->hdcShow, 0, 0, lw->width, lw->height, lw->hdcMem, 0, 0, SRCCOPY);
	}
	lw->CheckStop();
	return 0;
}

void DrawLine(HDC hdc, int x0, int y0, int x1, int y1, int width, COLORREF color) {
	HPEN hPen = CreatePen(PS_SOLID, width, color);
	HPEN oldHPen = (HPEN)SelectObject(hdc, hPen);
	
	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x1, y1);

	SelectObject(hdc, oldHPen);
	DeleteObject(hPen);
}

void DrawRect(HDC hdc, int x0, int y0, int x1, int y1,int width, COLORREF color) {
	DrawLine(hdc, x0, y0, x1, y0, width, color);
	DrawLine(hdc, x1, y0, x1, y1, width, color);
	DrawLine(hdc, x1, y1, x0, y1, width, color);
	DrawLine(hdc, x0, y1, x0, y0, width, color);
}
void DrawBmp(HDC hdc, HBITMAP hbmp, int x, int y, int dWidth, int dHeight, int u, int v, int sWidth, int sHeight, UINT crTransparent){
	HDC tempDC = CreateCompatibleDC(hdc);
	HBITMAP oldHbmp = (HBITMAP)SelectObject(tempDC, hbmp);
	TransparentBlt(hdc, x, y, dWidth, dHeight, tempDC, u, v, sWidth, sHeight, crTransparent);
	
	SelectObject(tempDC, oldHbmp);
	DeleteDC(tempDC);
}

void DrawHealth(HDC hdc, int x, int y, int width, int height, COLORREF color, int health, int maxHealth) {
	HBRUSH hbr = CreateSolidBrush(color);
	RECT rect;
	
	rect.left = x;
	rect.top = y;
	rect.right = x + width * health / maxHealth;
	rect.bottom = y + height;

	FillRect(hdc, &rect, hbr);

	DeleteObject(hbr);
}

void DrawNumber(HDC hdc, HBITMAP numsBmp, int num, int x, int y, int width, int height, int numWidth, int numHeight)
{
	int n = num;
	int b = 0;
	int p = 0;
	while (n = n/10) {
		b++;
	}
	for (int i = 0; i <= b; i++) {
		n = num % 10;
		DrawBmp(hdc, numsBmp, x + (b - i) * width, y, width, height, n * numWidth, 0, numWidth, numHeight, RGB(255, 255, 255));
		num = num / 10;
	}

}

void DrawSNumber(HDC hdc, HBITMAP numsBmp, int num, int x, int y, int width, int height, int numWidth, int numHeight)
{
	DrawBmp(hdc, numsBmp, x, y, width, height, num * numWidth, 0, numWidth, numHeight, RGB(255, 255, 255));
}

void FillRectA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
	HBRUSH hbr = CreateSolidBrush(color);
	RECT rc;
	rc.top = y1;
	rc.left = x1;
	rc.right = x2;
	rc.bottom = y2;

	FillRect(hdc, &rc, hbr);
	DeleteObject(hbr);
}

void DrawDNumber(HDC hdc, HBITMAP numsBmp, int num, int x, int y, int width, int height, int numWidth, int numHeight)
{
	int i = num / 10;
	DrawBmp(hdc, numsBmp, x, y, width, height, i * numWidth, 0, numWidth, numHeight, RGB(255, 255, 255));
	DrawBmp(hdc, numsBmp, x + width, y, width, height, num % 10 * numWidth, 0, numWidth, numHeight, RGB(255, 255, 255));
}
