#pragma once
#include<easyx.h>
class CGunner {
public:
	int m_x;
	int m_y;
	int step;
	int hurt;
	int state;
	IMAGE m_gun;
public:
	CGunner();
	virtual ~CGunner();
public:
	virtual void InitGunner(int x, int y)=0;
	virtual void ShowGunner()=0;
	void MoveGunner(int othergun, int pos, int state);
	virtual void choicegunner();
};