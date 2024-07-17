#pragma once
#include"../Player/Player.h"
class Gift  {
public:
	int m_x;
	int m_y;
	int m_is=0;
	IMAGE m_gift;
	void InitGift();
	void ShowGift();
	bool IsHitPlayer(CPlayer& player);
	void getGift(CPlayer& player,int* hurt);
};