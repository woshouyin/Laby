#define V_RIGHT			0x00
#define V_DOWN			0x01
#define V_LEFT			0x02
#define V_UP			0x03
#define PLAYER_MOVING	0x04
#define PLAYER_STOP		0x05
#define PLAYER_DEAD		0x06
#pragma once

class Map;

class Player {
public:
	int id, x, y;
	Map* map;
	Player(int id, int x, int y, int health);
	bool Move(int vector);
	int GetMode();
	void SetMode(int mode);
	int GetFace();
	void SetFace(int face);
	int GetHealth();
	void Kill();
	bool ChangeHealth(int dh);
	bool Attack();
	bool MoveAble();
	bool AttackAble();
	bool BeAttacked(Player *player, int injure);
private:
	int health, mode, face;
	int lastAtTick, lastAtedTick;
} ;