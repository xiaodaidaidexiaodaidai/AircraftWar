#pragma once
#include"../Player/Player.h"
#include<random>
using namespace std;
class CFoePlane {
public:
	int m_x;
	int m_y;
	IMAGE m_foe;
	int m_blood;
	int m_showId;
	static random_device rand;
public:
	CFoePlane();
	~CFoePlane();
public:
	virtual void InitFoe() = 0;
	virtual void ShowFoe()=0;
	void MoveFoe(int step);
	virtual bool IsHitPlayer(CPlayer& player)=0;
	virtual bool IsHitGunner(CGunner* pGun)=0;
	virtual CGunner* SendGun() = 0;
};