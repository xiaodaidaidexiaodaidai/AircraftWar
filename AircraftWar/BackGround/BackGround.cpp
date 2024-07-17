#include"Background.h"
#include"../GameConfig/GameConfig.h"
CBackGround::CBackGround() {
	m_x=0;
	m_y=0;
}
CBackGround::~CBackGround() {}
void CBackGround::InitBack() {
	m_x=0;
	m_y=-IMG_BACK_HEIGHT;
	::loadimage(&m_back,L"./res/±³¾°.jpg");
}
void CBackGround::ShowBack() {
	::putimage(m_x, m_y, &m_back);
}
void CBackGround::MoveBack(int step) {
	m_y += step;
	if (m_y >= 0) {
		m_y = -IMG_BACK_HEIGHT;
	}
}