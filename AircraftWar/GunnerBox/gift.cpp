#include"gift.h"
#include"../GameConfig/GameConfig.h"
void Gift::InitGift() {
	m_x = rand() % (IMG_BACK_WIDTH);
	m_y = rand() % (IMG_BACK_HEIGHT);
	m_is = 1;
	::loadimage(&m_gift, L"./res/gift.jpg");
}
void Gift::ShowGift() {
	::putimage(m_x, m_y,&m_gift, SRCPAINT);
}


bool Gift::IsHitPlayer(CPlayer& player) {
	//判断第一个点是否在矩形内
	int x1 = player.m_x + IMG_PLAYER_WIDTH / 2;
	if (m_x <= x1 && x1 <= m_x + IMG_FOE_SMA_WIDTH &&
		m_y <= player.m_y && player.m_y <= m_y + IMG_FOE_SMA_HEIGHT) {
		return true;
	}


	int y1 = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= player.m_x && player.m_x <= m_x + IMG_FOE_SMA_WIDTH &&
		m_y <= y1 && y1 <= m_y + IMG_FOE_SMA_HEIGHT) {
		return true;
	}


	int x2 = player.m_y + IMG_PLAYER_HEIGHT / 2;
	if (m_x <= x2 && x2 <= m_x + IMG_FOE_SMA_WIDTH &&
		m_y <= y1 && y1 <= m_y + IMG_FOE_SMA_HEIGHT) {
		return true;
	}

	return false;
}

void Gift::getGift(CPlayer& player,int* hurt)
{
	if (m_is == 1) {
		player.blood++;
		player.blue += 10;
		hurt++;
		m_is = 0;
	}

}



