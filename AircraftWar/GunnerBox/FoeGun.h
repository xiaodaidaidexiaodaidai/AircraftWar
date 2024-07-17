#pragma once
#include "Gunner.h"

class CFoeGunner : public CGunner {
public:
	CFoeGunner(int n, int s);

	~CFoeGunner();

	void InitGunner(int x, int y);

	void ShowGunner();
};