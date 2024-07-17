#pragma once
#include<list>
#include"Gunner.h"
using namespace std;
class CGunnerBox {
public:
	list<CGunner*> m_lstGun;
	list<CGunner*> m_lstGunBoom;
	list<CGunner*> m_lstLGun;
	list<CGunner*> m_lstRGun;
public:
	CGunnerBox();
	~CGunnerBox();
public:
	void ShowAllGunner(int othergun);
	void MoveAllGunner(int othergun);
};