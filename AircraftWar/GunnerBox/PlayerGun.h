#pragma once
#include "Gunner.h"

class CPlayerGunner : public CGunner {
public:
	CPlayerGunner(int n, int s);

	~CPlayerGunner();

	void InitGunner(int m, int n);

	void ShowGunner();

	void choicegunner();

};