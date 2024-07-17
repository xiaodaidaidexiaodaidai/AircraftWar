#pragma once
#include<easyx.h>
#include"../GunnerBox/Gunner.h"
class CPlayer {
public:
	int m_x;
	int m_y;
	int blood;
	int blue;
	int othergun;
	IMAGE m_player;
	IMAGE m_playerMask;
public:
	CPlayer();
	~CPlayer();
public:
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(WPARAM, int step);
	CGunner* SendGun();
	bool IsHitGunner(CGunner* pGun);
};