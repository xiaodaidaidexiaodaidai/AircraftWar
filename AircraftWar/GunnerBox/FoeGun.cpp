#include "FoeGun.h"
#include "../GameConfig/GameConfig.h"

CFoeGunner::CFoeGunner(int n, int s) {
	m_x = 0;
	m_y = 0;
	step = n;
	hurt = 1;
	state = s;
}
CFoeGunner::~CFoeGunner()
{
}

void CFoeGunner::InitGunner(int x, int y) {
	m_x = x;
	m_y = y;
	::loadimage(&m_gun, L"./res/gunnerp.jpg");
}

void CFoeGunner::ShowGunner() {
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_gun, IMG_GUNNER_WIDTH, 0, SRCPAINT);
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_gun, 0, 0, SRCAND);
}