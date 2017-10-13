#include  <iostream>
#include "Laby.h"
#include "LabyWindow.h"
#include "Timer.h"
#include "Player.h"
#include "Map.h"
#pragma 

int LabyWindow::winner = -1;

LabyWindow::LabyWindow(HINSTANCE hinstance, LPSTR name, int width, int height, Map *hmap) {
	LabyWindow::hinstance = hinstance;
	LabyWindow::name = name;
	LabyWindow::width = width;
	LabyWindow::height = height;
	LabyWindow::map = hmap;
	LabyWindow::BmpTitle = LoadBitmapFromFile("Title.bmp");
	LabyWindow::BmpWin[0] = LoadBitmapFromFile("WinP1.bmp");
	LabyWindow::BmpWin[1] = LoadBitmapFromFile("WinP2.bmp");
	LabyWindow::BmpFlag = LoadBitmapFromFile("Flag.bmp");
	LabyWindow::BmpTime = LoadBitmapFromFile("Time.bmp");
	LabyWindow::mapEdge = map->GetEdge()*lineLong;
	WNDCLASS wndCls;
	wrong = false;

	wndCls.hInstance = hinstance;
	wndCls.lpfnWndProc = WinProc;
	wndCls.cbClsExtra = 0;
	wndCls.cbWndExtra = 0;
	wndCls.style = CS_HREDRAW | CS_VREDRAW;
	wndCls.hIcon = NULL;
	wndCls.hCursor = NULL;
	wndCls.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wndCls.lpszClassName = name;
	wndCls.lpszMenuName = NULL;
	RegisterClass(&wndCls);
	hwnd = CreateWindow(
		name,
		name,
		WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXFULLSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYFULLSCREEN) - height) / 2,
		width,
		height,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	if (hwnd == NULL)
		wrong = true;
	hdc = GetDC(hwnd);
	hdcMem = CreateCompatibleDC(hdc);
	hdcBG = CreateCompatibleDC(hdcMem);
	hbmp = CreateCompatibleBitmap(hdc, width, height);
	hbmpBG = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(hdcMem, hbmp);
	SelectObject(hdcBG, hbmpBG);
	threadDraw = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Draw, this, CREATE_SUSPENDED, NULL);
}

LabyWindow::~LabyWindow() {
	DeleteDC(hdc);
	DeleteDC(hdcMem);
	DeleteDC(hdcBG);
	DeleteObject(hbmp);
	DeleteObject(hbmpBG);
	DeleteObject(BmpFlag);
	DeleteObject(BmpTitle);
	DeleteObject(BmpWin[0]);
	DeleteObject(BmpWin[1]);
	for (int i = 0; i < Map::playerNum; i++) {
		DeleteObject(BmpPlayer[i]);
	}
}

void LabyWindow::Run() {
	ShowWindow(hwnd, SW_SHOW);
	ResumeThread(threadDraw);
	Message();
}
void LabyWindow::Message() {
	MSG Msg;
	while (GetMessage(&Msg, hwnd, 0, 0) > 0) {
		//cout << "Message" << endl;
		//TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

HBITMAP LabyWindow::LoadBitmapFromFile(LPSTR file) {
	return (HBITMAP)LoadImage(hinstance, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

/*id ÊôÓÚ{0,1,2,3,4}*/
void LabyWindow::RegisterPlayerImg(int id, LPSTR file) {
	BmpPlayer[id] = LoadBitmapFromFile(file);
	BITMAP bmp;
	GetObject(BmpPlayer[id], sizeof(BITMAP), &bmp);
	PlayerImgSize[id] = bmp.bmHeight;
}

void LabyWindow::DrawPlayer(int id, int x, int y, int face) {
	DrawBmp(hdcMem, BmpPlayer[id], wallStartX + lineLong * x + 2, wallStartY + lineLong * y + 2, lineLong - 4, lineLong - 4,
		PlayerImgSize[id]*face , 0, PlayerImgSize[id], PlayerImgSize[id], RGB(255, 255, 255));
}

void LabyWindow::DrawWallLine(int type, int x, int y) {
	int sx = wallStartX + x * lineLong;
	int sy = wallStartY + y * lineLong;
	if (type)
		DrawLine(hdcBG, sx, sy, sx, sy + lineLong + 1, lineWidth, lineColor);
	else
		DrawLine(hdcBG, sx, sy, sx + lineLong + 1, sy, lineWidth, lineColor);
}

void LabyWindow::DrawWall() {
	int e = map->GetEdge();
	for (int i = 0; i < e; i++) {
		for (int t = 0; t < e + 1; t++) {
			if (map->GetAWall(i, t))
				DrawWallLine(0, i, t);
			if (map->GetBWall(t, i))
				DrawWallLine(1, t, i);
		}
	}
}

void LabyWindow::InitBG() {
	DrawWall();
	DrawBmp(hdcBG, BmpTitle, wallStartX, 0, mapEdge, wallStartY, 0, 0, 640, 70, RGB(255, 255, 255));
	DrawBmp(hdcBG, BmpPlayer[0], wallStartX, wallStartY + mapEdge, mapEdge / 9, mapEdge / 9
		, 0, 0, PlayerImgSize[0], PlayerImgSize[0], RGB(255, 255, 255));

	DrawBmp(hdcBG, BmpPlayer[1], wallStartX + mapEdge/2, wallStartY + mapEdge, mapEdge / 9, mapEdge / 9
		, 0, 0, PlayerImgSize[1], PlayerImgSize[1], RGB(255, 255, 255));
	
	DrawRect(hdcBG, wallStartX + mapEdge / 9 + 2, wallStartY + mapEdge * 37 / 36
		, wallStartX + mapEdge / 2 - 3, wallStartY + mapEdge * 39 / 36, 3, RGB(255, 255, 255));
	DrawRect(hdcBG, wallStartX + mapEdge * 11 / 18 + 2, wallStartY + mapEdge * 37 / 36
		, wallStartX + mapEdge - 3, wallStartY + mapEdge * 39 / 36, 3, RGB(255, 255, 255));
	DrawBmp(hdcBG, BmpFlag, wallStartX + flagX*lineLong + 1, wallStartY + flagY*lineLong + 1, lineLong - 1, lineLong - 1
			, 0, 0, lineLong - 1, lineLong - 1, RGB(255, 255, 255));
	DrawBmp(hdcBG, BmpTime, wallStartX + mapEdge, wallStartY, 270, 120, 0, 0, 270, 120, RGB(255, 255, 255));
}

void LabyWindow::Init() {
	InitBG();
}

void LabyWindow::Paint() {
	for (int i = 0; i < map->playerNum; i++) {
		if (map->players[i].GetMode() != PLAYER_DEAD) {
			DrawPlayer(i, map->players[i].x, map->players[i].y, map->players[i].GetFace());
		}
	}
	DrawHealth(hdcMem, wallStartX + mapEdge / 9 + 3, wallStartY + mapEdge * 37 / 36 + 2
		, mapEdge * 7 / 18 - 6, mapEdge / 18 - 2, RGB(255, 0, 0), map->players[0].GetHealth(), 20);
	DrawHealth(hdcMem, wallStartX + mapEdge * 11 / 18 + 3, wallStartY + mapEdge * 37 / 36 + 2
		, mapEdge * 7 / 18 - 6, mapEdge / 18 - 2, RGB(255, 0, 0), map->players[1].GetHealth(), 20);

	if (winner != -1) {
		DrawBmp(hdcMem, BmpWin[winner], wallStartX, wallStartY, mapEdge, mapEdge, 0, 0, mapEdge, mapEdge, RGB(255, 255, 255));
	}
		
}

void CheckWin(int id) {
	if (Map::players[id].x == LabyWindow::flagX && Map::players[id].y == LabyWindow::flagY && LabyWindow::winner == -1) {
		LabyWindow::winner = id;
	}
}

void MovePlayerByKey(int id, int vector) {
	if (( Map::playerNum > id && Map::players[id].GetFace() != PLAYER_DEAD 
		&& (Map::players[id].GetMode() == PLAYER_STOP || Map::players[id].GetFace() != vector))
		&& Map::players[id].MoveAble()){

		Map::players[id].SetFace(vector);
		Map::players[id].Move(vector);
		Map::players[id].SetMode(PLAYER_MOVING);
	}
	CheckWin(id);
}
void StopMovePlayerByKey(int id, int face) {
	if (Map::players[id].GetFace() == face && Map::playerNum > id && Map::players[id].GetMode() == PLAYER_MOVING) {
		Map::players[id].SetMode(PLAYER_STOP);
	}
}

void PlayerAttack(int id) {
	if (id < Map::playerNum)
		Map::players[id].Attack();
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	//cout << "msg:" << msg << endl;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		cout << "KeyDown:" << wParam << endl;
		switch (wParam) {
		case 'W':
			MovePlayerByKey(0, V_UP);
			break;
		case 'A':
			MovePlayerByKey(0, V_LEFT);
			break;
		case 'S':
			MovePlayerByKey(0, V_DOWN);
			break;
		case 'D':
			MovePlayerByKey(0, V_RIGHT);
			break;
		case 'J':
			PlayerAttack(0);
			break;
		case VK_UP:
			MovePlayerByKey(1, V_UP);
			break;
		case VK_DOWN:
			MovePlayerByKey(1, V_DOWN);
			break;
		case VK_LEFT:
			MovePlayerByKey(1, V_LEFT);
			break;
		case VK_RIGHT:
			MovePlayerByKey(1, V_RIGHT);
			break;
		case 13:
			PlayerAttack(1);
			break;
		default:
			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam) {
		case 'W':
			StopMovePlayerByKey(0, V_UP);
			break;
		case 'A':
			StopMovePlayerByKey(0, V_LEFT);
			break;
		case 'S':
			StopMovePlayerByKey(0, V_DOWN);
			break;
		case 'D':
			StopMovePlayerByKey(0, V_RIGHT);
			break;
		case VK_UP:
			StopMovePlayerByKey(1, V_UP);
			break;
		case VK_DOWN:
			StopMovePlayerByKey(1, V_DOWN);
			break;
		case VK_LEFT:
			StopMovePlayerByKey(1, V_LEFT);
			break;
		case VK_RIGHT:
			StopMovePlayerByKey(1, V_RIGHT);
			break;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}