#include "Player.h"
#include "Map.h"
#include <windows.h>
#pragma once

Player::Player(int id, int x, int y, int health) {
	Player::id = id;
	Player::x = x;
	Player::y = y;
	Player::health = health;
	Player::face = V_RIGHT;
	Player::mode = PLAYER_STOP;
	Player::lastAtTick = -5000;
	Player::lastAtedTick = -5000;
}

bool Player::Move(int vector) {
	SetFace(vector);
	switch (vector) {
	case V_UP:
		if (map->GetAWall(x, y)) return false ;
		if (map->HavePlayer(x, y - 1) != -1) return false;
		y--;
		return true;
	case V_DOWN:
		if (map->GetAWall(x, y + 1)) return false;
		if (map->HavePlayer(x, y + 1) != -1) return false;
		y++;
		return true;
	case V_LEFT:
		if (map->GetBWall(x, y)) return false;
		if (map->HavePlayer(x - 1, y) != -1) return false;
		x--;
		return true;
	case V_RIGHT:
		if (map->GetBWall(x + 1, y)) return false;
		if (map->HavePlayer(x + 1, y) != -1) return false;
		x++;
		return true;
	default:
		return false;
	}
}

int Player::GetMode() {
	return mode;
}

void Player::SetMode(int mode) {
	Player::mode = mode;
}

int Player::GetHealth() {
	return health;
}

bool Player::ChangeHealth(int dh) {
	health += dh;
	if (health <= 0) {
		health = 0;
		mode = PLAYER_DEAD;
		x = -1;
		y = -1;
		return false;
	}
	else {
		return true;
	}
}

int Player::GetFace() {
	return Player::face;
}

void Player::SetFace(int face) {
	Player::face = face;
}

void Player::Kill() {
	x = -1;
	y = -1;
	mode = PLAYER_DEAD;
}

bool Player::Attack() {
	DWORD nowTick = GetTickCount();
	int dx = x;
	int dy = y;
	bool wall = false;
	Player *dp = NULL;
	if (AttackAble()) {
		lastAtTick = nowTick;

		switch (face) {
		case V_UP:
			wall = map->GetAWall(x, y);
			break;
		case V_DOWN:
			wall = map->GetAWall(x, y + 1);
			break;
		case V_LEFT:
			wall = map->GetBWall(x, y);
			break;
		case V_RIGHT:
			wall = map->GetBWall(x + 1, y);
			break;
		default:
			wall = false;
			break;
		}
		if (wall) return false;
		
		switch (face)
		{
		case V_UP:
			dy--;
			break;
		case V_DOWN:
			dy++;
			break;
		case V_LEFT:
			dx--;
			break;
		case V_RIGHT:
			dx++;
			break;
		default:
			break;
		}

		for (int i = 0; i < map->playerNum; i++) {
			if (map->players[i].x == dx && map->players[i].y == dy)
				dp = map->players + i;
		}
		if (dp)
			return dp->BeAttacked(this, 5);
		else
			return false;
	}
	else {
		return false;
	}
}

bool Player::BeAttacked(Player *player, int injure) {
	if (MoveAble()) {
		lastAtedTick = GetTickCount();
		ChangeHealth(-injure);
		return true;
	}
	else {
		return false;
	}
}

bool Player::MoveAble() {
	DWORD nowTick = GetTickCount();
	if (nowTick - lastAtedTick > 500 && mode != PLAYER_DEAD)
		return true;
	else
		return false;
}

bool Player::AttackAble() {
	DWORD nowTick = GetTickCount();
	if (nowTick - lastAtedTick > 500 && nowTick - lastAtTick > 2000 && mode != PLAYER_DEAD)
		return true;
	else
		return false;
}
