#include"Gunner.h"
#include"../GameConfig/GameConfig.h"
CGunner::CGunner() {}
CGunner::~CGunner() {}


void CGunner::MoveGunner(int othergun,int pos,int state) {
	m_y += (step * 2);
	if (state == 0) {
		if (othergun == 2) {
			if (pos == 1) {
				m_x -= (step );
			}
			if (pos == 2) {
				m_x += (step );
			}
		}
	}
}

void CGunner::choicegunner()
{
	if (state == 0) {
		if (step < -10)step -= 5;
	}
}
