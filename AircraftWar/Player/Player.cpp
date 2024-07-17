#include"Player.h"
#include"../GameConfig/GameConfig.h"
#include"../GunnerBox/PlayerGun.h"
#include"../GunnerBox/FoeGun.h"
CPlayer::CPlayer():m_x(0),m_y(0),blood(3),othergun(0),blue(50) {
}
CPlayer::~CPlayer() {}
void CPlayer::InitPlayer() {
	m_x = (IMG_BACK_WIDTH - IMG_PLAYER_WIDTH) / 2;
	m_y = (IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT);
	::loadimage(&m_player, L"./res/playerplane.jpg");
	::loadimage(&m_playerMask, L"./res/playerplane-mask.jpg");
	}
void CPlayer::ShowPlayer() {
	::putimage(m_x, m_y, &m_playerMask, SRCPAINT);
	::putimage(m_x, m_y, &m_player, SRCAND);//Î»Óë
	}
void CPlayer::MovePlayer(WPARAM w, int step) {
	switch (w) {
	case  VK_LEFT:
		{
		if (m_x - step >= 0)m_x -= step;
		else m_x = 0;
		break;
		}
	case  VK_RIGHT:
	{
		if (m_x +step <= IMG_BACK_WIDTH - IMG_PLAYER_WIDTH)m_x += step;
		else m_x = IMG_BACK_WIDTH - IMG_PLAYER_WIDTH;
		break;
	}
	case  VK_UP:
	{
		if (m_y - step >= 0)m_y -= step;
		else m_y = 0;
		break;
	}
	case  VK_DOWN:
	{
		if (m_y + step <= IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT)m_y += step;
		else m_y = IMG_BACK_HEIGHT - IMG_PLAYER_HEIGHT;
		break;
	}

	}
	}
CGunner* CPlayer::SendGun() {
	CGunner* pGun=new CPlayerGunner(GUNNER_MOVE_STEP,0);
	int x = m_x + (IMG_PLAYER_WIDTH - IMG_GUNNER_WIDTH) / 2;
	int y = m_y - (IMG_GUNNER_HEIGHT);
	pGun->InitGunner(x, y);
	return pGun;
}

bool CPlayer::IsHitGunner(CGunner* pGun)
{
	int x = pGun->m_x + IMG_GUNNER_WIDTH / 2;
	int y = pGun->m_y + IMG_GUNNER_HEIGHT / 2;

	if (m_x <= x && x <= m_x + IMG_PLAYER_WIDTH &&
		m_y <= y && y <= m_y + IMG_PLAYER_HEIGHT) {
		return true;
	}
	return false;
}
