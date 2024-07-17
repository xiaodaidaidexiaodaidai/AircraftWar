#include"FoePlaneBox.h"
#include<typeinfo>
#include"FoePlaneBig.h"
#include"FoePlaneMid.h"
#include"FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"
CFoePlaneBox::CFoePlaneBox() {}
#define DELETE_FOE(FOE_LIST)\
list<CFoePlane*>::iterator ite##FOE_LIST=FOE_LIST.begin();\
		while(ite##FOE_LIST!=FOE_LIST.end()){\
		if(*ite##FOE_LIST){\
		delete(*ite##FOE_LIST);\
		(*ite##FOE_LIST)=nullptr;\
		}\
		ite##FOE_LIST++;\
		}\

CFoePlaneBox::~CFoePlaneBox() {
	DELETE_FOE(m_lstFoe)
	DELETE_FOE(m_lstFoeBoom)
}
void CFoePlaneBox::ShowAllFoe() {
	for (CFoePlane* foe : m_lstFoe) {
		if (foe) {
			foe->ShowFoe();
		}
	}
}
void CFoePlaneBox::MoveAllFoe() {
	list<CFoePlane*>::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end()) {

		if (*ite) {
			if (typeid(**ite) == typeid(CFoePlaneBig)) {
				(*ite)->MoveFoe(FOEBIG_MOVE_STEP);
			}
			if (typeid(**ite) == typeid(CFoePlaneMid)) {
				(*ite)->MoveFoe(FOEMID_MOVE_STEP);
			}
			if (typeid(**ite) == typeid(CFoePlaneSma)) {
				(*ite)->MoveFoe(FOESMA_MOVE_STEP);
			}
			if ((*ite)->m_y > IMG_BACK_HEIGHT) {
				delete(*ite);
				(*ite) = nullptr;
				ite = m_lstFoe.erase(ite);
				continue;
			}
		}
		ite++;
	}
}


void CFoePlaneBox::ShowAllBoomFoe() {
	for (CFoePlane* pFoe : m_lstFoeBoom) {
		if (pFoe) {
			pFoe->ShowFoe();
		}
	}
}