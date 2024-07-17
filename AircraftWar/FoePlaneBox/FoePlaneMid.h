#pragma once
#include"FoePlane.h"
class CFoePlaneMid :public CFoePlane {
public:
	void InitFoe();
	void ShowFoe();
	bool IsHitPlayer(CPlayer& player);
	bool IsHitGunner(CGunner* pGun);
	CGunner* SendGun();
};
