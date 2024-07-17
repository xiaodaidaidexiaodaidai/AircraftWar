#include "PlayerGun.h"
#include "../GameConfig/GameConfig.h"

CPlayerGunner::CPlayerGunner(int n, int s) {
	m_x = 0;
	m_y = 0;
	step = n;
	hurt = 1;
	state = s;
}

CPlayerGunner::~CPlayerGunner() {

}

void CPlayerGunner::InitGunner(int x, int y) {
	m_x = x;
	m_y = y;
	::loadimage(&m_gun, L"./res/gunner.jpg");
}

void CPlayerGunner::ShowGunner()
{
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_gun, IMG_GUNNER_WIDTH, 0, SRCPAINT);
	::putimage(m_x, m_y, IMG_GUNNER_WIDTH, IMG_GUNNER_HEIGHT, &m_gun, 0, 0, SRCAND);
}

void CPlayerGunner::choicegunner()
{
	if (state == 0) {
		if (step < -10)step -= 5;
	}
}
