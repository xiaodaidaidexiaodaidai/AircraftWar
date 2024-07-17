
#include"FoePlane.h"
CFoePlane::CFoePlane() {
	m_x = 0;
	m_y = 0;
	m_foe;
	m_blood = 0;
	m_showId = 0;
}
CFoePlane::~CFoePlane() {}

void CFoePlane::MoveFoe(int step) {
	m_y += step;
}
random_device CFoePlane::rand;
