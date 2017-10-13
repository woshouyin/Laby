#include <windows.h>
#include <iostream>
#pragma comment(lib,"msimg32.lib")
#define GetBit(i, bit) (((i) >> (bit)) & 0x01) 
#pragma once
using namespace std;

class LabyWindow;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI Draw(LabyWindow *lw);
void DrawLine(HDC hdc, int x0, int y0, int x1, int y1, int width, COLORREF color);
void DrawRect(HDC hdc, int x0, int y0, int x1, int y1, int width, COLORREF color);
void DrawBmp(HDC hdc, HBITMAP hbmp, int x, int y, int dWidth1, int dHeight, int u, int v, int sWidth, int sHeight, UINT crTransparent); 
void DrawHealth(HDC hdc, int x, int y, int width, int height, COLORREF color, int health, int maxHealth);
