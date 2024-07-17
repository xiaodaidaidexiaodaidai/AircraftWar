#include"FoePlaneMid.h"
#include"../GameConfig/GameConfig.h"
#include"../GunnerBox/FoeGun.h"
void CFoePlaneMid::InitFoe() {
	m_x = CFoePlane::rand() % (IMG_BACK_WIDTH - IMG_FOE_MID_WIDTH + 1);
	m_y = -IMG_FOE_MID_HEIGHT;
	::loadimage(&m_foe, L"./res/foeplanemid.jpg");
	m_blood = FOEMID_BLOOD;
	m_showId = 3;
}
void CFoePlaneMid::ShowFoe() {
	::putimage(m_x, m_y, IMG_FOE_MID_WIDTH, IMG_FOE_MID_HEIGHT,
		&m_foe, IMG_FOE_MID_WIDTH, (3 - m_showId) * IMG_FOE_MID_HEIGHT, SRCPAINT);
	::putimage(m_x, m_y, IMG_FOE_MID_WIDTH, IMG_FOE_MID_HEIGHT,
		&m_foe, 0, (3 - m_showId) * IMG_FOE_MID_HEIGHT, SRCAND);
}


bool CFoePlaneMid::IsHitPlayer(CPlayer& player) {
	//判断第一个点是否在矩形内
	int x1 = player.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x1 && x1 <= m_x + IMG_FOE_MID_WIDTH &&
		m_y <= player.m_y && player.m_y <= m_y + IMG_FOE_MID_HEIGHT) {
		return true;
	}


	int y1 = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= m_x + IMG_FOE_MID_WIDTH &&
		m_y <= y1 && y1 <= m_y + IMG_FOE_MID_HEIGHT) {
		return true;
	}


	int x2 = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= x2 && x2 <= m_x + IMG_FOE_MID_WIDTH &&
		m_y <= y1 && y1 <= m_y + IMG_FOE_MID_HEIGHT) {
		return true;
	}

	return false;
}

bool CFoePlaneMid::IsHitGunner(CGunner* pGun) {
	//取炮弹中心的点
	int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
	int y = pGun->m_y + IMG_GUNNER_HEIGHT / 2;

	if (m_x <= x && x <= m_x + IMG_FOE_MID_WIDTH &&
		m_y <= y && y <= m_y + IMG_FOE_MID_HEIGHT) {
		return true;
	}
	return false;
}

CGunner* CFoePlaneMid::SendGun()
{
	CGunner* pGun = new CFoeGunner(FOEMID_MOVE_STEP, 1);
	pGun->InitGunner(m_x + (IMG_FOE_MID_WIDTH - IMG_GUNNER_WIDTH) / 2, m_y + IMG_FOE_MID_HEIGHT + IMG_GUNNER_HEIGHT);
	return pGun;
}



